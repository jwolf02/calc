#include <str_utils.hpp>
#include <token.hpp>

std::vector<std::string> tokenize(const std::string &expression) {
  std::vector<std::string> result;
  std::string token;
  for (char c : expression) {
    if (c == ' ') {
      if (!token.empty()) {
        result.push_back(token);
        token.clear();
      }
    } else if (isOperator(std::string(&c, 1)) or c == '(' or c == ')' or c == ',') {
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

std::vector<std::string> preprocess(const std::vector<std::string> &tokens) {
  std::vector<std::string> tmp0;
  for (auto &token : tokens) {
    auto it = constants.find(token);
    if (it != constants.end())
      tmp0.push_back((*it).second);
    else
      tmp0.push_back(token);
  }

  std::vector<std::string> tmp1;
  for (int i = 0; i < (int) tmp0.size(); ++i) {
    if (i >= 1 and i < (int) (tmp0.size() - 2)
        and (tmp0[i - 1] == "(" and tmp0[i] == "-" and isNumber(tmp0[i +1]) and tmp0[i + 2] == ")")) {
      tmp1.push_back(tmp0[i] + tmp0[i + 1]);
      i += 1;
    } else {
      tmp1.push_back(tmp0[i]);
    }
  }

  return tmp1;
}

std::string postprocess(const std::string &result) {
  std::string str;
  std::size_t found;
  if ((found = result.find(".")) != std::string::npos) {
    int i = (int) result.size() - 1;
    while (i >= 0 and result[i] == '0')
      --i;
    str = result[i] == '.' ? result.substr(0, i) : result.substr(0, i + 1);
  } else {
    str = result;
  }

  return str != "-0" ? str : "0";
}
