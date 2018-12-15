#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <Parser.hpp>
#include <print_stl.hpp>
#include <ShuntingYard.hpp>
#include <Calculator.hpp>
#include <sstream>

static void print_help() {
  std::cout << "Example usage: eval \"(5 + 2) * sin(12.2) / (-99) - 0.05\"" << std::endl;
  std::cout << "Functions and Operators:" << std::endl;
  std::cout << "Basic arithmethic: {+, -, *, /, ^}" << std::endl;
  std::cout << "Trigonometrics:    {sin, cos, tan}" << std::endl;
  std::cout << "Miscellaneous:     {sqr, sqrt, cbrt, log, ln, exp}" << std::endl;
  std::cout << "Constants:         {e, pi}" << std::endl;
}

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0]
              << " <arithmethic expression> (type -h for help)" << std::endl;
    exit(1);
  } else if (std::string(argv[1]) == "-h") {
    print_help();
    exit(0);
  }

  try {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(10);

    for (int i = 1; i < argc; ++i) {
      std::string expression(argv[i]);
      expression = Parser::remove_whitespace(expression);

      std::vector<std::string> tokens = Parser::tokenize(expression);
      tokens = Parser::preprocess_negatives(tokens);
      tokens = ShuntingYard::convert(tokens);

      double result = Calculator::eval(tokens);
      if (argc > 2)
        std::cout << '(' << i << ") ";

      std::cout << Parser::remove_trailing_zeros(std::to_string(result)) << std::endl;
    }
  } catch (std::runtime_error &err) {
    std::cerr  << "Error: " << err.what() << std::endl;
  }

  return 0;
}
