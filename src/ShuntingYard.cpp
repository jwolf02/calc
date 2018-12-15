#include <ShuntingYard.hpp>
#include <vector>
#include <string>
#include <stack>
#include <stdexcept>
#include <unordered_set>
#include <regex>

#define LEFT  (0)
#define RIGHT (1)

static std::string pop_operator(std::stack<std::string> &operators) {
  std::string tmp = operators.top();
  operators.pop();
  return tmp;
}

static bool isNumber(const std::string &token) {
  const static std::regex number("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?");
  return std::regex_match(token, number);
}

static bool isOperator(const std::string &token) {
  const static std::unordered_set<std::string> operators = {
    "+", "-", "*", "/", "^"
  };
  return operators.find(token) != operators.end();
}

static bool isFunction(const std::string &token) {
  return !(isNumber(token) or isOperator(token) or token == "(" or token == ")");
}

static int precedence(const std::string &token) {
  if (token == "+" or token == "-") {
    return 2;
  } else if (token == "*" or token == "/") {
    return 3;
  } else if (token == "^") {
    return 4;
  } else if (isFunction(token)) {
    return 5;
  } else {
    return 1;
  }
}

static int associativity(const std::string &token) {
  if (token == "^")
    return RIGHT;
  else
    return LEFT;
}

std::vector<std::string> ShuntingYard::convert(const std::vector<std::string> &tokens) {
  std::vector<std::string> output;
  std::stack<std::string> operators;
  //print(tokens);
  for (auto &token : tokens) {
    //print(output);
    //print(std::vector<std::string>((&operators.top() + 1) - operators.size(), &operators.top() + 1));
    if (isNumber(token)) {
      output.push_back(token);
    } else if (isFunction(token)) {
      operators.push(token);
    } else if (isOperator(token)) {
      while (!operators.empty() and
              (isFunction(operators.top())
              or (precedence(operators.top()) > precedence(token))
              or ( (precedence(operators.top()) == precedence(token))
                    and (associativity(operators.top()) == LEFT ) )
              )
              and (operators.top() != "(")
            ) {
        output.push_back(pop_operator(operators));
      }
      operators.push(token);
    } else if (token == "(") {
      operators.push(token);
    } else if (token == ")") {
      while (!operators.empty() and (operators.top() != "(")) {
        output.push_back(pop_operator(operators));
      }

      if (operators.empty()) {
        throw std::runtime_error("Unmatched parenthese");
      } else {
        operators.pop();
      }
    } else {
      throw std::runtime_error("Unrecognized token '" + token + "'");
    }
  }

  while (!operators.empty()) {
    if (operators.top() == "(" or operators.top() == ")")
      throw std::runtime_error("Unmatched parenthese");

    output.push_back(pop_operator(operators));
  }

  return output;
}
