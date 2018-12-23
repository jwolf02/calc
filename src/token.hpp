#ifndef __TOKEN_HPP
#define __TOKEN_HPP

#include <string>
#include <functional>
#include <unordered_map>

#define LEFT  0
#define RIGHT 1

namespace token {

    typedef std::function<double(double)> func;
    typedef std::function<double(double, double)> op;

    bool is_operator(const std::string &token);

    bool is_function(const std::string &token);

    func get_function(const std::string &token);

    op get_operator(const std::string &token);

    double get_variable(const std::string &token);

    void add_variable(const std::string &token, double val);

    bool is_number(const std::string &token);

    bool is_variable(const std::string &token);

    int precedence(const std::string &token);

    int associativity(const std::string &token);

}

#endif // __TOKEN_HPP
