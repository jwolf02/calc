#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <shunting_yard.hpp>
#include <str_utils.hpp>
#include <token.hpp>
#include <calc.hpp>

static void print_help() {
  std::cout << "Example usage: eval \"(5 + 2) * sin(12.2) / (-99) - 0.05\"" << std::endl;
  std::cout << "Functions and Operators:" << std::endl;
  std::cout << "Basic arithmethic:  {+, -, *, /, ^, mod}" << std::endl;
  std::cout << "Trigonometrics:     {sin, cos, tan, asin, acos, atan}" << std::endl;
  std::cout << "Hyperbolics:        {sinh, cosh, tanh, asinh, acosh, atanh}" << std::endl;
  std::cout << "Miscellaneous:      {sqr, sqrt, cbrt, log2, log10, ln, log, exp, min, max}" << std::endl;
  std::cout << "Rounding functions: {ceil, floor, abs}" << std::endl;
  std::cout << "Constants:          {e, pi}" << std::endl;
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
    for (int i = 1; i < argc; ++i) {

      double result = eval(
                        convert_to_rpn(
                          preprocess(
                            tokenize(argv[i])
                          )));
      if (argc > 2)
        std::cout << '(' << i << ") ";

      std::cout << postprocess(std::to_string(result)) << std::endl;
    }
  } catch (std::runtime_error &err) {
    std::cerr  << "Error: " << err.what() << std::endl;
  }

  return 0;
}
