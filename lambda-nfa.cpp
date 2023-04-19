#include "lambda-nfa.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

LambdaNFA::LambdaNFA(int initialState){
    this->Q.push_back(initialState);
    this->initialState = initialState;
    this->F[initialState] = false;
}

LambdaNFA::LambdaNFA(const LambdaNFA& obj){
    this->Q = obj.Q;
    this->initialState = obj.initialState;
    for(int elem: obj.Q) {
        if (!obj.transition[elem].empty())
            this->transition[elem] = obj.transition[elem];
        this->F[elem] = obj.F.at(elem);
    }
}

LambdaNFA& LambdaNFA::operator=(const LambdaNFA& obj){
    if(this != &obj){
        this->Q = obj.Q;
        this->initialState = obj.initialState;
        for(int elem: obj.Q) {
            if (!obj.transition[elem].empty())
                this->transition[elem] = obj.transition[elem];
            this->F[elem] = obj.F.at(elem);
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const LambdaNFA& obj){
    out << "Automata nodes:";
    for(int i = 0; i < obj.Q.size(); ++i)
    {
        out << " " << obj.Q[i];
    }
    out << '\n';
    out << "Initial state: " << obj.initialState << '\n';
    out << "Final states:";
    for(int i = 0; i < obj.Q.size(); ++i)
    {
        if(obj.F.at(obj.Q[i]))
            out << " " << obj.Q[i];
    }
    out << "\nTransitions:\n";
    for(int elem: obj.Q) {
        if (!obj.transition[elem].empty()){
            for(auto i = obj.transition[elem].begin(); i != obj.transition[elem].end(); ++i) {
                out << elem << " " << i->first << " ";
                for(const auto& setElem: i->second)
                    out << setElem << " ";
                out << "\n";
            }
        }
    }
    return out;
}

void LambdaNFA::addTransition(int startState, char letter, int endState){
    if(std::find(Q.begin(), Q.end(), startState) == Q.end()){
        this->Q.push_back(startState);
    }
    if(std::find(Q.begin(), Q.end(), endState) == Q.end()){
        this->Q.push_back(endState);
    }
    transition[startState][letter].insert(endState);
    if(F[startState] != true)
        F[startState] = false;
    if(F[endState] != true)
        F[endState] = false;
    std::sort(this->Q.begin(), this->Q.end());
}

void LambdaNFA::addFinalState(int finalState, bool final){
    F[finalState] = final;
}

void LambdaNFA::readFromFile(const std::string& filename)
{
    std::ifstream f1(filename);
    f1 >> this->initialState;
    int temp, node1, node2;
    char letter;
    std::string s;
    std::getline(f1, s);
    std::stringstream ss(s);
    while(ss >> temp)
        addFinalState(temp, 1);
    while(f1)
    {   
        f1 >> node1;
        f1 >> letter;
        f1 >> node2;
        addTransition(node1, letter, node2);
    }
}

void LambdaNFA::lambda_paths(std::unordered_set<int>& currentStates, std::unordered_set<int> &states)
{
    std::unordered_set<int> tempStates; // The nodes where the current states have lambda-paths
    bool allEquals = true;
    for(auto state: states){
        currentStates.insert(state);
        tempStates = transition[state]['#'];
        for(auto elem: tempStates)
        {
            if(std::find(currentStates.begin(), currentStates.end(), elem) == currentStates.end())
                allEquals = false;
        }
        if(allEquals == false)
            lambda_paths(currentStates, this->transition[state]['#']);
    }
}

void LambdaNFA::transitionNormalisation(std::unordered_map<int, int> changes) {
    for(int& elem: this->Q)
    {
        if(!transition[elem].empty())
        {
            for(auto i = this->transition[elem].begin(); i != this->transition[elem].end(); ++i) {
                std::vector<int> temp;
                temp.insert(temp.end(), i->second.begin(), i->second.end());
                i->second.clear();
                for(int pos = 0; pos < temp.size(); ++pos){
                    i->second.insert(changes[temp[pos]]);
                }
                temp.clear();
            }
            transition[changes[elem]] = transition[elem];
            if(changes[elem] != elem)
                transition[elem].clear();
        }
    }
}

void LambdaNFA::normalisation(LambdaNFA& L1, LambdaNFA& L2){
    int maxNode = 0;
    std::unordered_map<int, int> changes; // changes[previousNode] = newNode
    L1.initialState = maxNode;
    for(int i = 0; i < L1.Q.size(); ++i){
        changes[L1.Q[i]] = maxNode++;
        L1.F[changes[L1.Q[i]]] = false;
        if(L1.F[L1.Q[i]])
        {
            L1.F[L1.Q[i]] = false;
            L1.F[changes[L1.Q[i]]] = true;
        }
    }
    L1.transitionNormalisation(changes);
    for(int i = 0; i < L1.Q.size(); ++i){
        L1.Q[i] = changes[L1.Q[i]];
    }
    changes.clear();
    L2.initialState = maxNode;
    for(int i = 0; i < L2.Q.size(); ++i){
        changes[L2.Q[i]] = maxNode++;
        L2.F[changes[L2.Q[i]]] = false;
        if(L2.F[L2.Q[i]])
        {
            L2.F[L2.Q[i]] = false;
            L2.F[changes[L2.Q[i]]] = true;
        }
    }
    L2.transitionNormalisation(changes);
    for(int i = 0; i < L2.Q.size(); ++i){
        L2.Q[i] = changes[L2.Q[i]];
    }
}

LambdaNFA LambdaNFA::concatenation(LambdaNFA& L1, LambdaNFA& L2){
    LambdaNFA::normalisation(L1, L2);
    LambdaNFA L = L1;
    for(int i = 0; i < L.Q.size(); ++i)
        if(L.F[Q[i]] == true)
        {
            L.F[Q[i]] = false;
            L.addTransition(Q[i], '#', L2.initialState);
        }
}

//int main(){
//    LambdaNFA obj;
//     obj.addTransition(0, "#", 2);
//     obj.addTransition(0, "1", 1);
//     obj.addTransition(0, "2", 3);
//     obj.addTransition(1, "1", 0);
//     obj.addTransition(2, "#", 0);
//     obj.addTransition(2, "0", 4);
//     obj.addTransition(2, "2", 3);
//     obj.addTransition(3, "2", 0);
//     obj.addTransition(3, "2", 2);
//     obj.addTransition(4, "0", 2);
//     obj.addFinalState(2, 1);
//     obj.addFinalState(0, 1);
//
//
//    obj.addTransition(0, "#", 1);
//    obj.addTransition(0, "b", 1);
//    obj.addTransition(0, "#", 3);
//    obj.addTransition(1, "b", 2);
//    obj.addTransition(2, "a", 1);
//    obj.addTransition(3, "b", 0);
//    obj.addTransition(3, "#", 1);
//    obj.addTransition(3, "#", 2);
//    obj.addTransition(3, "a", 4);
//    obj.addTransition(3, "a", 3);
//    obj.addTransition(4, "#", 2);
//    obj.addTransition(4, "b", 4);
//    obj.addTransition(4, "b", 3);
//    obj.addFinalState(0, 1);
//
//    std::vector<int> path;
//    path.assign(6, -1);
//    obj.depthSearch(path, {0}, 0, "aababb");
//    obj.printPaths();
//    // std::unordered_set<int> temp = {0};
//    // obj.lambda_paths(temp, temp);
//    // for(auto elem: temp)
//    //     std::cout << elem << " ";
//    return 0;
//}