#include <calc.hpp>
#include <vector>
#include <string>
#include <functional>
#include <cmath>
#include <regex>
#include <token.hpp>
#include <expression.hpp>

// compute result
static double eval(const std::vector<std::string> &tokens) {
  std::vector<double> result;

  for (auto &token : tokens) {
    if (isVariable(token)) {
      result.push_back((*variables.find(token)).second);
    } else if (isNumber(token)) {
      double val = std::stod(token);
      result.push_back(val);
      continue;
    } else if (functions.find(token) != functions.end()) {
      if (result.empty())
        throw std::runtime_error("syntax error: no argument for function '" + token + "'");

      auto func = (*functions.find(token)).second;
      double a = result.back();
      result.pop_back();
      result.push_back(func(a));

    } else if (operators.find(token) != operators.end()) {
      if (result.size() < 2)
        throw std::runtime_error("syntax error: no operands for operator '" + token + "'");

      auto op = (*operators.find(token)).second;
      double b = result.back();
      result.pop_back();
      double a = result.back();
      result.pop_back();
      result.push_back(op(a, b));

    } else {
      throw std::runtime_error("syntax error: unexspected token '" + token + "'");
    }
  }

  if (result.size() != 1)
    throw std::runtime_error("syntax error: remaining temporary on stack");
  else
    return result.front();
}

double calc::evaluate(const std::string &expression) {
  std::vector<std::string> tokens = expression::tokenize(expression);
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
  const double result = eval(expression::to_postfix(
          expression::preprocess_negatives(tokens)));

  // if assignment
  if (!var_name.empty()) {
    variables[var_name] = result;
  }

  return result;
}