#include <Calculator.hpp>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include <functional>
#include <cmath>
#include <regex>
#include <stdexcept>

static const std::unordered_map<std::string, double> constants = {
  {"pi", 3.14159265358979323846},
  {"e", 2.71828182845904523536},
  {"inf", INFINITY}
};

static const std::unordered_map<std::string, std::function<double (double)>> functions = {
  {"sin", [](double a) { return std::sin(a); }},
  {"cos", [](double a) { return std::cos(a); }},
  {"tan", [](double a) { return std::tan(a); }},
  {"sqrt", [](double a) { return a >= 0 ? std::sqrt(a) : throw std::runtime_error("Negative operand in sqrt"); }},
  {"cbrt", [](double a) { return std::cbrt(a); }},
  {"sqr", [](double a) { return a * a; }},
  {"log", [](double a) { return a >= 0 ? std::log2(a) : throw std::runtime_error("Negative operand in log"); }},
  {"ln", [](double a) { return a >= 0 ? std::log(a) : throw std::runtime_error("Negative operand in log"); }},
  {"exp", [](double a) { return std::exp(a); }}
};

static const std::unordered_map<std::string, std::function<double (double, double)>> operators = {
  {"+", [](double a, double b) { return a + b; }},
  {"-", [](double a, double b) { return a - b; }},
  {"*", [](double a, double b) { return a * b; }},
  {"/", [](double a, double b) { return b != 0.0 ? a / b : throw std::runtime_error("Division by 0"); }},
  {"^", [](double a, double b) { return std::pow(a, b); }}
};

static bool isNumber(const std::string &token) {
  const static std::regex number("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?");
  return std::regex_match(token, number);
}

double Calculator::eval(const std::vector<std::string> &tokens) {
  std::vector<double> result;

  for (auto &token : tokens) {
    if (isNumber(token)) {
      double val = std::stod(token);
      result.push_back(val);
      continue;
    } else if (constants.find(token) != constants.end()) {
      auto c = (*constants.find(token)).second;
      result.push_back(c);
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
