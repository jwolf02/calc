#include <Parser.hpp>
#include <string>
#include <unordered_set>
#include <regex>

static bool isNumber(const std::string &token) {
  const static std::regex number("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?");
  return std::regex_match(token, number);
}

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

std::vector<std::string> Parser::preprocess_negatives(const std::vector<std::string> &tokens) {
  std::vector<std::string> tmp;
  for (int i = 0; i < (int) tokens.size(); ++i) {
    if (i >= 1 and i < (int) (tokens.size() - 2)
        and (tokens[i - 1] == "(" and tokens[i] == "-" and isNumber(tokens[i +1]) and tokens[i + 2] == ")")) {
      tmp.push_back(tokens[i] + tokens[i + 1]);
      i += 1;
    } else {
      tmp.push_back(tokens[i]);
    }
  }

  return tmp;
}

std::string Parser::remove_trailing_zeros(const std::string &result) {
  int i = (int) result.size() - 1;
  while (i >= 0 and (result[i] == '0' or result[i] == '.'))
    --i;
  return result.substr(0, i + 1);
}
