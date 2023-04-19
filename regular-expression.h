//
// Created by gfa on 4/18/23.
//

#ifndef REGULAR_EXPRESSION_TO_LAMBDA_NFA_REGULAR_EXPRESSION_H
#define REGULAR_EXPRESSION_TO_LAMBDA_NFA_REGULAR_EXPRESSION_H

#include "lambda-nfa.h"
#include <iostream>

class RegularExpression{
public:
    static LambdaNFA constructLetter(char letter){
        LambdaNFA L;
        if(letter == '#'){
            L.addFinalState(0, true);
        }
        else {
            L.addTransition(0, letter, 1);
            L.addFinalState(1, true);
        }
        return L;
    }

};

#endif //REGULAR_EXPRESSION_TO_LAMBDA_NFA_REGULAR_EXPRESSION_H
