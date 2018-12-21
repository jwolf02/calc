#ifndef __STR_UTILS_HPP
#define __STR_UTILS_HPP

#include <vector>
#include <string>

namespace expression {

    // split expression string to vector of tokens
    std::vector<std::string> tokenize(const std::string &expression);

    // preprocess negatives by deciding whether a '-' is a subtraction of negation
    std::vector<std::string> preprocess_negatives(const std::vector<std::string> &tokens);

    // convert expression given in infix notation to postfix notation
    std::vector<std::string> to_postfix(const std::vector<std::string> &tokens);

}

#endif // __STR_UTILS_HPP
