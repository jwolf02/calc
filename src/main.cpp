#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <calc.hpp>
#include <sstream>
#include <expression.hpp>

static void print_help() {
  std::cout << "Usage: calc [expression [expression] ..]" << std::endl;
  std::cout << "Functions and Operators:" << std::endl;
  std::cout << "Basic arithmethic:  {+, -, *, /, ^, mod}" << std::endl;
  std::cout << "Trigonometrics:     {sin, cos, tan, asin, acos, atan}" << std::endl;
  std::cout << "Hyperbolics:        {sinh, cosh, tanh, asinh, acosh, atanh}" << std::endl;
  std::cout << "Miscellaneous:      {sqr, sqrt, cbrt, log2, log10, ln, log, exp, min, max}" << std::endl;
  std::cout << "Rounding functions: {ceil, floor, abs}" << std::endl;
  std::cout << "Constants:          {e, pi, inf}" << std::endl;
}

static std::string strip_trailing_zeros(const std::string &result) {
    std::string str;
    std::size_t found;
    if ((found = result.find('.')) != std::string::npos) {
        int i = (int) result.size() - 1;
        while (i >= 0 and result[i] == '0')
            --i;
        str = result[i] == '.' ? result.substr(0, i) : result.substr(0, i + 1);
    } else {
        str = result;
    }

    return str != "-0" ? str : "0";
}

static std::string to_string(double r) {
  std::stringstream oss;
  oss << std::fixed << std::setprecision(15) << r;
  std::string str;
  oss >> str;
  return strip_trailing_zeros(str);
}

int main(int argc, const char *argv[]) {
  if (argc > 1 && std::string(argv[1]) == "--help") {
    print_help();
    exit(0);
  }

  try {

    if (argc > 2) {
      // batch mode
      for (int i = 1; i < argc; ++i) {
        if (argc > 2)
          std::cout << "(" << i << ") ";
        std::cout << to_string(calc::evaluate(argv[i])) << std::endl;
      }
    } else
      // interactive mode
      while (true) {
        std::cout << "> " << std::flush;

        std::string expr;
        std::getline(std::cin, expr);
        if (!expr.empty()) {
          // exit
          if (expr == "q" || expr == "quit")
            break;

          // evaluate entered expression
          std::cout << to_string(calc::evaluate(expr)) << std::endl;
        }
      }

  } catch (std::runtime_error &err) {
    std::cerr << err.what() << std::endl;
  }

  return 0;
}
