#ifndef __SHUNTING_YARD_HPP
#define __SHUNTING_YARD_HPP

#include <vector>
#include <string>

namespace ShuntingYard {

std::string remove_whitespace(const std::string &str);

std::vector<std::string> tokenize(const std::string &expression);

std::vector<std::string> preprocess_negatives(const std::vector<std::string> &tokens);

std::vector<std::string> convert(const std::vector<std::string> &tokens);

}

#endif // __SHUNTING_YARD_HPP
