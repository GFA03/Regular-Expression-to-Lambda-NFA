#ifndef REGULAR_EXPRESSIONS_TO_LAMBDA_NFA_H
#define REGULAR_EXPRESSIONS_TO_LAMBDA_NFA_H
// #pragma

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

class LambdaNFA{
    int initialState;
    std::vector<int> Q; // Nodes
    std::unordered_map<int, bool> F; // Final states
    std::unordered_map<std::string, std::unordered_set<int>> transition[200]; // Transition function

    std::vector<int> result[100] = {};
    int k = 0;
    
public:
    std::unordered_map<std::string, std::unordered_set<int>> getQ() const;

    LambdaNFA(int initialState = 0);
    
    LambdaNFA(const LambdaNFA& obj);
    
    LambdaNFA& operator= (const LambdaNFA& obj);

    void readFromFile(const std::string& filename);
    
    void addTransition(int startState, std::string letter, int endState);

    void addFinalState(int finalState, bool final);

    friend std::ostream& operator<<(std::ostream &out, const LambdaNFA& obj);

    void depthSearch(std::vector<int> &path, std::unordered_set<int> currentState, int depth, std::string word);

    void lambda_paths(std::unordered_set<int> &currentStates, std::unordered_set<int> &states);

    void printPaths();
};

#endif //REGULAR_EXPRESSIONS_TO_LAMBDA_NFA_H