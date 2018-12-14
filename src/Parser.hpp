#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <string>
#include <vector>

namespace Parser {

std::string remove_whitespace(const std::string &expression);

std::vector<std::string> tokenize(const std::string &expression);

}

#endif // __PARSER_HPP
