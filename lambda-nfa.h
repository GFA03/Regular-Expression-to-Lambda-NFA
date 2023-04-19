#ifndef REGULAR_EXPRESSIONS_TO_LAMBDA_NFA_H
#define REGULAR_EXPRESSIONS_TO_LAMBDA_NFA_H

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

class LambdaNFA{
    int initialState;
    std::vector<int> Q; // Nodes
    std::unordered_map<int, bool> F; // Final states
    std::unordered_map<char, std::unordered_set<int>> transition[200]; // Transition function
    
public:
    explicit LambdaNFA(int initialState = 0);
    
    LambdaNFA(const LambdaNFA& obj);
    
    LambdaNFA& operator= (const LambdaNFA& obj);
    
    void addTransition(int startState, char letter, int endState);

    void addFinalState(int finalState, bool final);

    friend std::ostream& operator<<(std::ostream &out, LambdaNFA& obj);

    void transitionNormalisation(std::unordered_map<int, int> changes); // iterates through L1 transitions and replaces previousNode with newNode

    static void normalisation(LambdaNFA& L1, LambdaNFA& L2); // Makes sure that L1 and L2 have different numbers for nodes

    static LambdaNFA unions(LambdaNFA& L1, LambdaNFA& L2);

    static LambdaNFA concatenation(LambdaNFA& L1, LambdaNFA& L2);

    static LambdaNFA star(LambdaNFA& L1);
};

#endif //REGULAR_EXPRESSIONS_TO_LAMBDA_NFA_H