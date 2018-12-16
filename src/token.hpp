#ifndef __TOKEN_HPP
#define __TOKEN_HPP

#include <string>
#include <functional>
#include <unordered_map>

#define LEFT  0
#define RIGHT 1

typedef std::function<double (double)> func;
typedef std::function<double (double, double)> op;

bool isOperator(const std::string &token);

bool isFunction(const std::string &token);

bool isNumber(const std::string &token);

bool isConstant(const std::string &token);

double to_double(const std::string &token);

int precedence(const std::string &token);

int associativity(const std::string &token);

extern const std::unordered_map<std::string, func> functions;

extern const std::unordered_map<std::string, op> operators;

extern const std::unordered_map<std::string, std::string> constants;

#endif // __TOKEN_HPP
