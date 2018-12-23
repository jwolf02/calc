#include <calc.hpp>
#include <vector>
#include <string>
#include <functional>
#include <cmath>
#include <regex>
#include <token.hpp>
#include <print_stl.hpp>
#include <error.hpp>

using namespace token;

static std::vector<std::string> tokenize(const std::string &expression) {
  std::vector<std::string> result;
  std::string token;
  for (const char c : expression) {
    if (c == ' ') {
      if (!token.empty()) {
        result.push_back(token);
        token.clear();
      }
    } else if (is_operator(std::string(&c, 1)) or c == '(' or c == ')' or c == ',' or c == '=' or c == '!') {
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
        (i < ((int) tokens.size() - 1) && tokens[i] == "-" && (tokens[i - 1] == "(" || is_operator(tokens[i - 1])))) {
      // check if following token represents number | constant | variable
      if (is_number(tokens[i + 1]) || is_variable(tokens[i + 1])) {
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

static void pop_operator(std::vector<std::string> &ops, std::vector<double> &result) {
  // get function/operator token
  const std::string &token = ops.back();

  if (is_function(token)) {
    if (result.empty())
      throw std::runtime_error("syntax error: no argument for '" + token + "'");

    // call func with top value on result stack
    auto func = get_function(token);
    double a = pop(result);
    result.push_back(func(a));
  } else if (is_operator(token)) {
    if (result.size() < 2)
      throw std::runtime_error("syntax error: '" + token + "' requires 2 arguments");

    // call operator with two top values on result stack
    auto op = get_operator(token);
    double b = pop(result);
    double a = pop(result);
    result.push_back(op(a, b));
  } else {
    UNEXPECTED_TOKEN(token);
  }

  // remove token from stack
  ops.pop_back();
}

static double eval(const std::vector<std::string> &tokens) {
  std::vector<std::string> operators;
  std::vector<double> result;
  for (auto &token : tokens) {
    if (is_variable(token)) {
      // load variable value and push to stack
      result.push_back(get_variable(token));
    } else if (is_number(token)) {
      // push constant value
      result.push_back(std::stod(token));
    } else if (token == ",") {
      // apply all operators
      while (!operators.empty() and
             operators.back() != "(") {
        pop_operator(operators, result);
      }
    } else if (is_function(token)) {
      // call function
      operators.push_back(token);
    } else if (is_operator(token)) {
      // call operators
      while (!operators.empty() and
             (is_function(operators.back())
              or (precedence(operators.back()) > precedence(token))
              or ( (precedence(operators.back()) == precedence(token))
                   and (associativity(operators.back()) == LEFT ) )
             )
             and (operators.back() != "(")
              ) {
        pop_operator(operators, result);
      }
      operators.push_back(token);
    } else if (token == "(") {
      // just push it
      operators.push_back(token);
    } else if (token == ")") {
      // apply all operators until opening brace is found
      while (!operators.empty() and (operators.back() != "(")) {
        pop_operator(operators, result);
      }

      if (operators.empty()) {
        UNMATCHED_PARENTHESE;
      } else {
        operators.pop_back();
      }
    } else {
      UNEXPECTED_TOKEN(token);
    }
  }

  while (!operators.empty()) {
    if (operators.back() == "(" or operators.back() == ")") {
      UNMATCHED_PARENTHESE;
    }

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
      UNEXPECTED_TOKEN(var_name);

    // erase first two tokens and evaluate remaining expression
    tokens.erase(tokens.begin(), tokens.begin() + 2);
  }

  // compute result
  tokens = preprocess_negatives(tokens);
  const double result = eval(tokens);


  // if assignment
  if (!var_name.empty()) {
    add_variable(var_name, result);
  }

  return result;
}