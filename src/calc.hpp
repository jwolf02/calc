#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP

#include <string>
#include <vector>

namespace calc {

    /*
     * Compute the result from the string expression
     * Expression has to be in infix notation
     */
    double evaluate(const std::string &expression);

}

#endif // __CALCULATOR_HPP
