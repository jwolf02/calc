#include <calc.hpp>
#include <vector>
#include <string>
#include <functional>
#include <cmath>
#include <token.hpp>

double eval(const std::vector<std::string> &tokens) {
  std::vector<double> result;

  for (auto &token : tokens) {
    if (isNumber(token)) {
      double val = std::stod(token);
      result.push_back(val);
      continue;
    } else if (functions.find(token) != functions.end()) {
      if (result.size() == 0)
        throw std::runtime_error("No argument for function");

      auto func = (*functions.find(token)).second;
      double a = result.back();
      result.pop_back();
      result.push_back(func(a));

    } else if (operators.find(token) != operators.end()) {
      if (result.size() < 2)
        throw std::runtime_error("No operands for operator");

      auto op = (*operators.find(token)).second;
      double b = result.back();
      result.pop_back();
      double a = result.back();
      result.pop_back();
      result.push_back(op(a, b));

    } else {
      throw std::runtime_error("Unknown token '" + token + "'");
    }
  }

  if (result.size() != 1)
    throw std::runtime_error("Result stack is empty!");
  else
    return result[0];
}
