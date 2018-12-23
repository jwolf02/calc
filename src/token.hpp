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

func getFunction(const std::string &token);

op getOperator(const std::string &token);

double getVariable(const std::string &token);

void addVariable(const std::string &token, double val);

bool isNumber(const std::string &token);

bool isVariable(const std::string &token);

int precedence(const std::string &token);

int associativity(const std::string &token);

#endif // __TOKEN_HPP
