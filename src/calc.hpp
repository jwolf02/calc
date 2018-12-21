#ifndef __CALCULATOR_HPP
#define __CALCULATOR_HPP

#include <string>

namespace calc {

    // evaluate the expression given in postfix notation with preprocessed negatives
    double evaluate(const std::string &expression);

}

#endif // __CALCULATOR_HPP
