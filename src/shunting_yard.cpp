#include <shunting_yard.hpp>
#include <token.hpp>
#include <vector>
#include <string>
#include <stack>
#include <stdexcept>

static std::string pop_operator(std::stack<std::string> &operators) {
  std::string tmp = operators.top();
  operators.pop();
  return tmp;
}

std::vector<std::string> convert_to_rpn(const std::vector<std::string> &tokens) {
  std::vector<std::string> output;
  std::stack<std::string> operators;
  //print(tokens);
  for (auto &token : tokens) {
    //print(output);
    //print(std::vector<std::string>((&operators.top() + 1) - operators.size(), &operators.top() + 1));
    if (isNumber(token)) {
      output.push_back(token);
    } else if (token == ",") {
      while (!operators.empty() and
             operators.top() != "(") {
        output.push_back(pop_operator(operators));
      }
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
