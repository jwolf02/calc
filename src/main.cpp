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
  std::cout << "Example usage: eval \"(5 + 2) * 12.2 / 99 - 0.05\"" << std::endl;
  std::cout << "Operators:" << std::endl;
  std::cout << "Add: +" << std::endl;
  std::cout << "Sub: -" << std::endl;
  std::cout << "Mul: *" << std::endl;
  std::cout << "Div: /" << std::endl;
  std::cout << "Braces: ()" << std::endl;
}

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0]
              << " <arithmethic expression> (type -h for  help)" << std::endl;
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

      ss << result;
      std::string tmp;
      ss >> tmp;
      std::cout << Parser::remove_trailing_zeros(tmp) << std::endl;
    }
  } catch (std::runtime_error &err) {
    std::cerr  << "Error: " << err.what() << std::endl;
  }

  return 0;
}
