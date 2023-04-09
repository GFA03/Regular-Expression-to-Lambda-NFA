#ifndef REGULAR_EXPRESSIONS_TO_#_NFA_H
#define REGULAR_EXPRESSIONS_TO_#_NFA_H

#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

class LambdaNFA{
    int initialState;
    std::unordered_map<int, bool> F;
    std::unordered_map<std::string, std::unordered_set<int>> Q[200];

    std::vector<int> result[100] = {};
    int k = 0;
public:
    LambdaNFA(int initialState = 0);
    
    LambdaNFA(const LambdaNFA& obj);
    
    LambdaNFA& operator= (const LambdaNFA& obj);

    void readFromFile(const std::string& filename);
    
    void addTransition(int startState, std::string letter, int endState);

    void addFinalState(int finalState, bool final);

    friend std::ostream& operator<<(std::ostream &out, const LambdaNFA& obj);

    void depthSearch(std::vector<int> &path, std::unordered_set<int> currentState, int depth, std::string word);
};

#endif //SD_SORTER_H