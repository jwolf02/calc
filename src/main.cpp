#include <iostream>
#include <cstdlib>
#include <string>
#include <Parser.hpp>
#include <print_stl.hpp>

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

  std::string expression(argv[1]);
  expression = Parser::remove_whitespace(expression);
  std::vector<std::string> tokens = Parser::tokenize(expression);
  print(tokens);

  return 0;
}
