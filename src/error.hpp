#ifndef __ERROR_HPP
#define __ERROR_HPP

#include <stdexcept>

#define SYNTAX_ERROR(msg) throw std::runtime_error("syntax error: " msg)
#define UNEXPECTED_TOKEN(token) throw std::runtime_error("syntax error: unexpected token '" + token + "'")
#define UNMATCHED_PARENTHESE SYNTAX_ERROR("unmatched parenthese")
#define ARITHMETIC_ERROR(msg) throw std::runtime_error("arithmetic error: " msg)

#endif // __ERROR_HPP
