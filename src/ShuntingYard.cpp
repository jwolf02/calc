#include <ShuntingYard.hpp>
#include <vector>
#include <string>
#include <regex>
#include <stack>
#include <queue>
#include <unordered_map>
#include <functional>

typedef std::function<double (double)> UnaryOperator;
typedef std::funciton<double (double, double)> BinaryOperator;

static const std::unordered_map<std::string, UnaryOperator> functions;
static const std::unordered_map<std::string, BinaryOperator> operators = {
  {"+", Operator::add},
  {"-", Operator::sub},
  {"*", Operator::mul},
  {"/", Operator::div}
};

static bool isNumber(const std::string &token) {
  const static std::regex regex("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?");
  return regex_match(token, regex);
}

double ShuntingYard::eval(const std::vector<std::string> &tokens) {

  const static std::unordered_map<std::string, int> op_prec = {
    {'+', 0}, {'-', 0}, {'*', 1}, {'/', 1}, {'^', 2}
  };

  std::vector<std::string> rpn(tokens.size());
  std::stack<std::string> ops;

  for (auto &token : tokens) {
    if (isNumber(token)) {
      rpn.push_back(Token::number(token));
    } else if (token == '(') {
      ops.push_back(token);
    }
  }
}
