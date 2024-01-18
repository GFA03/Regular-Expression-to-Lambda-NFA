//
// Created by gfa on 4/18/23.
//

#include "regular-expression.h"
#include <stack>

LambdaNFA RegularExpression::constructLetter(char letter)
{
    LambdaNFA L;
    if (letter == '#')
    {
        L.addFinalState(0, true);
    }
    else
    {
        L.addTransition(0, letter, 1);
        L.addFinalState(1, true);
    }
    return L;
}

std::string RegularExpression::toRPN(const std::string &expr)
{
    std::stack<char> operators;
    std::string output = "";

    for (char letter : expr)
    {
        if (std::isalpha(letter))
            output.push_back(letter);
        else if (letter == '[')
            operators.push(letter);
        else if (letter == ']')
        {
            while (operators.top() != '[')
            {
                output.push_back(operators.top());
                operators.pop();
            }
            operators.pop();
        }
        else
        {
            while (!operators.empty() && operators.top() != '[' && (precedence[operators.top()] > precedence[letter]))
            {
                output.push_back((operators.top()));
                operators.pop();
            }
            operators.push(letter);
        }
    }
    while (!operators.empty())
    {
        output.push_back(operators.top());
        operators.pop();
    }
    return output;
}
