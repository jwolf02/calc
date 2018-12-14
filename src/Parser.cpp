#include <Parser.hpp>
#include <string>
#include <unordered_set>

std::string Parser::remove_whitespace(const std::string &expression) {
  std::string result;
  for (char c : expression) {
    if (c != ' ') {
      result.push_back(c);
    }
  }

  return result;
}

std::vector<std::string> Parser::tokenize(const std::string &expression) {
  std::vector<std::string> result;
  std::string token;
  std::unordered_set<char> operators = { '+', '-', '*', '/', '^', '(', ')'};
  for (char c : expression) {
    if (operators.find(c) != operators.end()) {
      if (!token.empty()) {
        result.push_back(token);
        token.clear();
      }
      result.push_back(std::string(1, c));
    } else {
      token.push_back(c);
    }
  }
  if (!token.empty())
    result.push_back(token);

  return result;
}
