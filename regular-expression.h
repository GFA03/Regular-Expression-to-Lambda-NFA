//
// Created by gfa on 4/18/23.
//

#ifndef REGULAR_EXPRESSION_TO_LAMBDA_NFA_REGULAR_EXPRESSION_H
#define REGULAR_EXPRESSION_TO_LAMBDA_NFA_REGULAR_EXPRESSION_H

#include "lambda-nfa.h"
#include <iostream>

class RegularExpression{
    static std::unordered_map<char, int> precedence;
public:
    static LambdaNFA constructLetter(char letter);

    static std::string toRPN(const std::string& expr);
};

inline std::unordered_map<char, int> RegularExpression::precedence = {
        {'+', 1},
        {'*', 2},
        {'^', 3}
};

#endif //REGULAR_EXPRESSION_TO_LAMBDA_NFA_REGULAR_EXPRESSION_H
