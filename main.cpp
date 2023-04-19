//
// Created by gfa on 4/18/23.
//

#include "regular-expression.h"
#include <stack>
#include <iostream>

std::unordered_map<char, int> precedence = {
        {'+', 1},
        {'*', 2},
        {'^', 3}
};

std::string toRPN(const std::string& expr){
    std::stack<char> operators;
    std::string output = "";

    for(char letter: expr){
        if(std::isalpha(letter))
            output.push_back(letter);
        else if(letter == '[')
            operators.push(letter);
        else if(letter == ']'){
            while(operators.top() != '['){
                output.push_back(operators.top());
                operators.pop();
            }
            operators.pop();
        }
        else{
            while(!operators.empty() && operators.top() != '[' && (precedence[operators.top()] > precedence[letter]))
            {
                output.push_back((operators.top()));
                operators.pop();
            }
            operators.push(letter);
        }
    }
    while(!operators.empty()){
        output.push_back(operators.top());
        operators.pop();
    }
    return output;
}

int main(){
//    std::string expr = "[[a*b]^*a]^";
//    std::cout << toRPN(expr);
//    LambdaNFA L;
//    L = RegularExpression::constructLetter('a');
//    LambdaNFA obj;
//     obj.addTransition(0, '#', 2);
//     obj.addTransition(0, '1', 1);
//     obj.addTransition(0, '2', 3);
//     obj.addTransition(1, '1', 0);
//     obj.addTransition(2, '#', 0);
//     obj.addTransition(2, '0', 4);
//     obj.addTransition(2, '2', 3);
//     obj.addTransition(3, '2', 0);
//     obj.addTransition(3, '2', 2);
//     obj.addTransition(4, '0', 2);
//     obj.addFinalState(2, 1);
//     obj.addFinalState(0, 1);
//
//    LambdaNFA obj2;
//    obj2.addTransition(0, '#', 1);
//    obj2.addTransition(0, 'b', 1);
//    obj2.addTransition(0, '#', 3);
//    obj2.addTransition(1, 'b', 2);
//    obj2.addTransition(2, 'a', 1);
//    obj2.addTransition(3, 'b', 0);
//    obj2.addTransition(3, '#', 1);
//    obj2.addTransition(3, '#', 2);
//    obj2.addTransition(3, 'a', 4);
//    obj2.addTransition(3, 'a', 3);
//    obj2.addTransition(4, '#', 2);
//    obj2.addTransition(4, 'b', 4);
//    obj2.addTransition(4, 'b', 3);
//    obj2.addFinalState(0, 1);
}