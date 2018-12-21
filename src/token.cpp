#include <token.hpp>
#include <regex>
#include <unordered_map>
#include <functional>
#include <string>
#include <cmath>

const std::unordered_map<std::string, func> functions = {
  {"sin", [](double a) { return std::sin(a); }},
  {"cos", [](double a) { return std::cos(a); }},
  {"tan", [](double a) { return std::tan(a); }},
  {"sqrt", [](double a) { return a >= 0 ? std::sqrt(a) : throw std::runtime_error("arithmetic error: negative operand in 'sqrt()'"); }},
  {"cbrt", [](double a) { return std::cbrt(a); }},
  {"sqr", [](double a) { return a * a; }},
  {"log2", [](double a) { return a >= 0 ? std::log2(a) : throw std::runtime_error("arithmetic : negative operand in 'log2()'"); }},
  {"log10", [](double a) { return a >= 0 ? std::log10(a) : throw std::runtime_error("arithmetic error: negative operand in 'log10()'"); }},
  {"ln", [](double a) { return a >= 0 ? std::log(a) : throw std::runtime_error("arithmetic error: negative operand in 'ln()'"); }},
  {"exp", [](double a) { return std::exp(a); }},
  {"asin", [](double a) { return std::asin(a); }},
  {"acos", [](double a) { return std::acos(a); }},
  {"atan", [](double a) { return std::atan(a); }},
  {"sinh", [](double a) { return std::sinh(a); }},
  {"cosh", [](double a) { return std::cosh(a); }},
  {"tanh", [](double a) { return std::tanh(a); }},
  {"abs", [](double a) { return std::abs(a); }},
  {"ceil", [](double a) { return std::ceil(a); }},
  {"floor", [](double a) { return std::floor(a); }},
  {"trunc", [](double a) { return std::trunc(a); }},
  {"asinh", [](double a) { return std::asinh(a); }},
  {"acosh", [](double a) { return std::acosh(a); }},
  {"atanh", [](double a) { return std::atanh(a); }}
};

const std::unordered_map<std::string, op> operators = {
  {"+", [](double a, double b) { return a + b; }},
  {"-", [](double a, double b) { return a - b; }},
  {"*", [](double a, double b) { return a * b; }},
  {"/", [](double a, double b) { return b != 0.0 ? a / b : throw std::runtime_error("arithmetic error: division by 0"); }},
  {"^", [](double a, double b) { return std::pow(a, b); }},
  {"max", [](double a, double b) { return a > b ? a : b; }},
  {"min", [](double a, double b) { return a < b ? a : b; }},
  {"log", [](double a, double b) { return a >= 0 and b >= 0 ? std::log(b) / std::log(a) : throw std::runtime_error("arithmetic error: negative operand in 'log()'"); }},
  {"mod", [](double a, double b) { return b != 0 ? std::fmod(a, b) : throw std::runtime_error("arithmetic error: division by 0"); }}
};

std::unordered_map<std::string, double> variables = {
  {"pi", M_PI},
  {"e", M_E},
  {"inf", INFINITY}
};

bool isOperator(const std::string &token) {
  return operators.find(token) != operators.end();
}

bool isFunction(const std::string &token) {
  return functions.find(token) != functions.end();
}

bool isNumber(const std::string &token) {
  const static std::regex number("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?");
  return std::regex_match(token, number);
}

bool isVariable(const std::string &token) {
  return variables.find(token) != variables.end();
}

int precedence(const std::string &token) {
  if (token == "+" or token == "-") {
    return 2;
  } else if (token == "*" or token == "/") {
    return 3;
  } else if (token == "^") {
    return 4;
  } else if (isFunction(token)) {
    return 5;
  } else if (token == "!") {
    return 6;
  } else {
    return 4;
  }
}

int associativity(const std::string &token) {
  if (token == "^")
    return RIGHT;
  else
    return LEFT;
}
