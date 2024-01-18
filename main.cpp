//
// Created by gfa on 4/18/23.
//

#include "regular-expression.h"
#include <stack>

int main()
{
    std::string expr;
    std::cin >> expr;
    std::cout << RegularExpression::toRPN(expr);
    std::stack<LambdaNFA> operators;
    std::string exprRPN = RegularExpression::toRPN(expr);
    for (char letter : exprRPN)
    {
        if (std::isalpha(letter))
        {
            LambdaNFA L;
            L = RegularExpression::constructLetter(letter);
            operators.push(L);
        }
        else
        {
            switch (letter)
            {
            case '+':
            {
                LambdaNFA L1, L2;
                L2 = operators.top();
                operators.pop();
                L1 = operators.top();
                operators.pop();
                operators.push(LambdaNFA::unions(L1, L2));
                break;
            }
            case '*':
            {
                LambdaNFA L1, L2;
                L2 = operators.top();
                operators.pop();
                L1 = operators.top();
                operators.pop();
                operators.push(LambdaNFA::concatenation(L1, L2));
                break;
            }
            case '^':
            {
                LambdaNFA L1;
                L1 = operators.top();
                operators.pop();
                operators.push(LambdaNFA::star(L1));
                break;
            }
            default:
            {
                std::cout << "Expresie invalida!";
                break;
            }
            }
        }
    }
    std::cout << operators.top();
}