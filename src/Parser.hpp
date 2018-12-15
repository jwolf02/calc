#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <string>
#include <vector>

namespace Parser {

std::string remove_whitespace(const std::string &expression);

std::vector<std::string> tokenize(const std::string &expression);

std::vector<std::string> preprocess_negatives(const std::vector<std::string> &tokens);

std::string remove_trailing_zeros(const std::string &result);

}

#endif // __PARSER_HPP
