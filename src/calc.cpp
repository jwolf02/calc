#include <calc.hpp>
#include <vector>
#include <string>
#include <functional>
#include <cmath>
#include <regex>
#include <token.hpp>

static std::vector<std::string> tokenize(const std::string &expression) {
  std::vector<std::string> result;
  std::string token;
  for (const char c : expression) {
    if (c == ' ') {
      if (!token.empty()) {
        result.push_back(token);
        token.clear();
      }
    } else if (isOperator(std::string(&c, 1)) or c == '(' or c == ')' or c == ',' or c == '=') {
      if (!token.empty()) {
        result.push_back(token);
        token.clear();
      }
      result.emplace_back(std::string(1, c));
    } else {
      token.push_back(c);
    }
  }
  if (!token.empty())
    result.push_back(token);

  return result;
}

static std::vector<std::string> preprocess_negatives(const std::vector<std::string> &tokens) {
  std::vector<std::string> tmp;
  tmp.reserve(tokens.size());

  for (int i = 0; i < (int) tokens.size(); ++i) {
    // decide whether '-' is subtraction or negation
    if ((i == 0 && tokens.front() == "-" && tokens.size() >= 2) ||
        (i < ((int) tokens.size() - 1) && tokens[i] == "-" && (tokens[i - 1] == "(" || isOperator(tokens[i - 1])))) {
      // check if following token represents number | constant | variable
      if (isNumber(tokens[i + 1]) || isVariable(tokens[i + 1])) {
        tmp.emplace_back("(");

        // insert negation (-1* token )
        tmp.emplace_back("-1");
        tmp.emplace_back("*");

        tmp.push_back(tokens[i + 1]);
        tmp.emplace_back(")");
        i += 1;
      } else {
        // following token is function or operator
        tmp.emplace_back("-1");
        tmp.emplace_back("*");
      }
    } else {
      // none of the above so token is simply appended
      tmp.push_back(tokens[i]);
    }
  }

  return tmp;
}

template <typename T>
static T pop(std::vector<T> &stack) {
  T val = stack.back();
  stack.pop_back();
  return val;
}

static void pop_operator(std::stack<std::string> &ops, std::vector<double> &result) {
  // get function/operator token
  const std::string &token = ops.top();

  if (isFunction(token)) {
    if (result.empty())
      throw std::runtime_error("syntax error: no argument for '" + token + "'");

    // call func with top value on result stack
    auto func = getFunction(token);
    double a = pop(result);
    result.push_back(func(a));
  } else if (isOperator(token)) {
    if (result.size() < 2)
      throw std::runtime_error("syntax error: '" + token + "' requires 2 arguments");

    // call operator with two top values on result stack
    auto op = getOperator(token);
    double b = pop(result);
    double a = pop(result);
    result.push_back(op(a, b));
  } else {
    throw std::runtime_error("syntax error: unexspected token '" + token + "'");
  }

  // remove token from stack
  ops.pop();
}

static double eval(const std::vector<std::string> &tokens) {
  std::stack<std::string> operators;
  std::vector<double> result;
  for (auto &token : tokens) {
    if (isVariable(token)) {
      // load variable value and push to stack
      result.push_back(getVariable(token));
    } else if (isNumber(token)) {
      // push constant value
      result.push_back(std::stod(token));
    } else if (token == ",") {
      // apply all operators
      while (!operators.empty() and
             operators.top() != "(") {
        pop_operator(operators, result);
      }
    } else if (isFunction(token)) {
      // call function
      operators.push(token);
    } else if (isOperator(token)) {
      // call operators
      while (!operators.empty() and
             (isFunction(operators.top())
              or (precedence(operators.top()) > precedence(token))
              or ( (precedence(operators.top()) == precedence(token))
                   and (associativity(operators.top()) == LEFT ) )
             )
             and (operators.top() != "(")
              ) {
        pop_operator(operators, result);
      }
      operators.push(token);
    } else if (token == "(") {
      // just push it
      operators.push(token);
    } else if (token == ")") {
      // apply all operators until opening brace is found
      while (!operators.empty() and (operators.top() != "(")) {
        pop_operator(operators, result);
      }

      if (operators.empty()) {
        throw std::runtime_error("syntax error: unmatched parenthese");
      } else {
        operators.pop();
      }
    } else {
      throw std::runtime_error("syntax error: unexspected token '" + token + "'");
    }
  }

  while (!operators.empty()) {
    if (operators.top() == "(" or operators.top() == ")")
      throw std::runtime_error("syntax error: unmatched parenthese");

    pop_operator(operators, result);
  }

  if (result.size() == 1) {
    return result.front();
  } else {
    throw std::runtime_error("syntax error: result stack size is not 1");
  }
}


double calc::evaluate(const std::string &expression) {
  std::vector<std::string> tokens = tokenize(expression);
  std::string var_name;

  // check if expression contains assignment
  if (tokens.size() > 1 && tokens[1] == "=") {
    var_name = tokens[0];

    // check if variable name satisfy regular expression [A-Z | a-z][A-Z | a-z | 0-9]*
    const static std::regex var_regexpr("[[:alpha:]][[:alnum:]]*");
    if (!std::regex_match(var_name, var_regexpr))
      throw std::runtime_error("syntax error: unexpected token '" + var_name + "'");

    // erase first two tokens and evaluate remaining expression
    tokens.erase(tokens.begin(), tokens.begin() + 2);
  }

  // compute result
  tokens = preprocess_negatives(tokens);
  const double result = eval(tokens);


  // if assignment
  if (!var_name.empty()) {
    addVariable(var_name, result);
  }

  return result;
}