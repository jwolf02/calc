#include <token.hpp>
#include <regex>
#include <unordered_map>
#include <functional>
#include <string>
#include <cmath>
#include <error.hpp>

using namespace token;

static double factorial(double a) {
  if (a - std::trunc(a) != 0 || a < 0)
    ARITHMETIC_ERROR("factorial has to be called with positive integral argument");

  unsigned long long val = 1;
  for (unsigned long long i = 1; i <= (unsigned long long) a; ++i)
    val *= i;

  return (double) val;
}

const static std::unordered_map<std::string, func> functions = {
  {"sin", [](double a) { return std::sin(a); }},
  {"cos", [](double a) { return std::cos(a); }},
  {"tan", [](double a) { return std::tan(a); }},
  {"sqrt", [](double a) { return a >= 0 ? std::sqrt(a) : ARITHMETIC_ERROR("negative operand in 'sqrt()'"); }},
  {"cbrt", [](double a) { return std::cbrt(a); }},
  {"sqr", [](double a) { return a * a; }},
  {"log2", [](double a) { return a >= 0 ? std::log2(a) : ARITHMETIC_ERROR("negative operand in 'log2()'"); }},
  {"log10", [](double a) { return a >= 0 ? std::log10(a) : ARITHMETIC_ERROR("negative operand in 'log10()'"); }},
  {"ln", [](double a) { return a >= 0 ? std::log(a) : ARITHMETIC_ERROR("negative operand in 'ln()'"); }},
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
  {"atanh", [](double a) { return std::atanh(a); }},
  {"!", [](double a) { return factorial(a); }}
};

const static std::unordered_map<std::string, op> operators = {
  {"+", [](double a, double b) { return a + b; }},
  {"-", [](double a, double b) { return a - b; }},
  {"*", [](double a, double b) { return a * b; }},
  {"/", [](double a, double b) { return b != 0.0 ? a / b : ARITHMETIC_ERROR("division by 0"); }},
  {"^", [](double a, double b) { return std::pow(a, b); }},
  {"max", [](double a, double b) { return a > b ? a : b; }},
  {"min", [](double a, double b) { return a < b ? a : b; }},
  {"log", [](double a, double b) { return a >= 0 and b >= 0 ? std::log(b) / std::log(a) : ARITHMETIC_ERROR("negative operand in 'log()'"); }},
  {"root", [](double a, double b) { return a >= 0 and b >= 0 ? std::pow(b, 1 / a) : ARITHMETIC_ERROR("negative operand in 'root()'"); }},
  {"mod", [](double a, double b) { return b != 0 ? std::fmod(a, b) : ARITHMETIC_ERROR("division by 0"); }},
  {"binomial", [](double a, double b) { return a >= b ? factorial(a) / (factorial(b) * factorial(a - b)) : ARITHMETIC_ERROR("n must be greater or equal to k"); }}
};

static std::unordered_map<std::string, double> variables = {
  {"pi", M_PI},
  {"e", M_E},
  {"inf", INFINITY}
};

bool token::is_operator(const std::string &token) {
  return operators.find(token) != operators.end();
}

bool token::is_function(const std::string &token) {
  return functions.find(token) != functions.end();
}

func token::get_function(const std::string &token) {
  return (*functions.find(token)).second;
}

op token::get_operator(const std::string &token) {
  return (*operators.find(token)).second;
}

double token::get_variable(const std::string &token) {
  return (*variables.find(token)).second;
}

void token::add_variable(const std::string &token, double val) {
  variables[token] = val;
}

bool token::is_number(const std::string &token) {
  const static std::regex number("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?");
  return std::regex_match(token, number);
}

bool token::is_variable(const std::string &token) {
  return variables.find(token) != variables.end();
}

int token::precedence(const std::string &token) {
  if (token == "+" or token == "-") {
    return 2;
  } else if (token == "*" or token == "/") {
    return 3;
  } else if (token == "^") {
    return 4;
  } else if (is_function(token)) {
    return 5;
  } else if (token == "!") {
    return 6;
  } else {
    return 4;
  }
}

int token::associativity(const std::string &token) {
  if (token == "^")
    return RIGHT;
  else
    return LEFT;
}
