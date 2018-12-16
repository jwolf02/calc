#ifndef __STR_UTILS_HPP
#define __STR_UTILS_HPP

#include <vector>
#include <string>

std::vector<std::string> tokenize(const std::string &expression);

std::vector<std::string> preprocess(const std::vector<std::string> &tokens);

std::string postprocess(const std::string &result);

#endif // __STR_UTILS_HPP
