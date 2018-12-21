#include <expression.hpp>
#include <token.hpp>
#include <stack>

std::vector<std::string> expression::tokenize(const std::string &expression) {
    std::vector<std::string> result;
    std::string token;
    for (const char c : expression) {
        if (c == ' ') {
            if (!token.empty()) {
                result.push_back(token);
                token.clear();
            }
        } else if (isOperator(std::string(&c, 1)) or c == '(' or c == ')' or c == ',' or c == '=') {
            if (!token.empty()) {
                result.push_back(token);
                token.clear();
            }
            result.emplace_back(std::string(1, c));
        } else {
            token.push_back(c);
        }
    }
    if (!token.empty())
        result.push_back(token);

    return result;
}

std::vector<std::string> expression::preprocess_negatives(const std::vector<std::string> &tokens) {
    std::vector<std::string> tmp;
    tmp.reserve(tokens.size());

    for (int i = 0; i < (int) tokens.size() && tokens.size() >= 2; ++i) {
        // decide whether '-' is subtraction or negation
        if ((i == 0 && tokens.front() == "-" && tokens.size() >= 2) ||
                (i < ((int) tokens.size() - 1) && tokens[i] == "-" && (tokens[i - 1] == "(" || isOperator(tokens[i - 1])))) {
            // check if following token represents number | constant | variable
            if (isNumber(tokens[i + 1]) || isVariable(tokens[i + 1])) {
                tmp.emplace_back("(");

                // insert negation (-1* token )
                tmp.emplace_back("-1");
                tmp.emplace_back("*");

                tmp.push_back(tokens[i + 1]);
                tmp.emplace_back(")");
                i += 1;
            } else {
                // following token is function or operator
                tmp.emplace_back("-1");
                tmp.emplace_back("*");
            }
        } else {
            // none of the above so token is simply appended
            tmp.push_back(tokens[i]);
        }
    }

    return tmp;
}

static std::string pop_operator(std::stack<std::string> &operators) {
    const std::string tmp = operators.top();
    operators.pop();
    return tmp;
}

std::vector<std::string> expression::to_postfix(const std::vector<std::string> &tokens) {
    std::vector<std::string> output;
    std::stack<std::string> operators;
    //print(tokens);
    for (auto &token : tokens) {
        //print(output);
        //print(std::vector<std::string>((&operators.top() + 1) - operators.size(), &operators.top() + 1));
        if (isNumber(token) || isVariable(token)) {
            output.push_back(token);
        } else if (token == ",") {
            while (!operators.empty() and
                   operators.top() != "(") {
                output.push_back(pop_operator(operators));
            }
        } else if (isFunction(token)) {
            operators.push(token);
        } else if (isOperator(token)) {
            while (!operators.empty() and
                   (isFunction(operators.top())
                    or (precedence(operators.top()) > precedence(token))
                    or ( (precedence(operators.top()) == precedence(token))
                         and (associativity(operators.top()) == LEFT ) )
                   )
                   and (operators.top() != "(")
                    ) {
                output.push_back(pop_operator(operators));
            }
            operators.push(token);
        } else if (token == "(") {
            operators.push(token);
        } else if (token == ")") {
            while (!operators.empty() and (operators.top() != "(")) {
                output.push_back(pop_operator(operators));
            }

            if (operators.empty()) {
                throw std::runtime_error("syntax error: unmatched parenthese");
            } else {
                operators.pop();
            }
        } else {
            throw std::runtime_error("syntax error: unexspected token '" + token + "'");
        }
    }

    while (!operators.empty()) {
        if (operators.top() == "(" or operators.top() == ")")
            throw std::runtime_error("syntax error: unmatched parenthese");

        output.push_back(pop_operator(operators));
    }

    return output;
}


