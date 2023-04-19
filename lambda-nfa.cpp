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
        try {
            this->F[elem] = obj.F.at(elem);
        }catch(std::out_of_range&){}
    }
}

LambdaNFA& LambdaNFA::operator=(const LambdaNFA& obj){
    if(this != &obj){
        this->Q = obj.Q;
        this->initialState = obj.initialState;
        for(int elem: obj.Q) {
            if (!obj.transition[elem].empty())
                this->transition[elem] = obj.transition[elem];
            try {
                this->F[elem] = obj.F.at(elem);
            }catch(std::out_of_range&){}
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, LambdaNFA& obj){
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
        try {
            if (obj.F[obj.Q[i]])
                out << " " << obj.Q[i];
        }
        catch (std::out_of_range){

        }
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
    if(!F[startState])
        F[startState] = false;
    if(!F[endState])
        F[endState] = false;
    std::sort(this->Q.begin(), this->Q.end());
}

void LambdaNFA::addFinalState(int finalState, bool final){
    F[finalState] = final;
}
void LambdaNFA::transitionNormalisation(std::unordered_map<int, int> changes) {
    std::unordered_map<char, std::unordered_set<int>> tempTransition[200];
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
                tempTransition[changes[elem]][i->first] = i->second;
            }
                transition[elem].clear();
        }
    }
    for(int& elem: this->Q)
        this->transition[changes[elem]] = tempTransition[changes[elem]];
}

void LambdaNFA::normalisation(LambdaNFA& L1, LambdaNFA& L2){
    int maxNode = 0;
    std::unordered_map<int, bool> temp;
    std::unordered_map<int, int> changes; // changes[previousNode] = newNode
    L1.initialState = maxNode;
    for(int i = 0; i < L1.Q.size(); ++i){
        changes[L1.Q[i]] = maxNode++;
        if(L1.F[L1.Q[i]])
        {
            L1.F[L1.Q[i]] = false;
            temp[changes[L1.Q[i]]] = true;
        }
    }
    L1.transitionNormalisation(changes);
    for(int i = 0; i < L1.Q.size(); ++i){
        L1.Q[i] = changes[L1.Q[i]];
    }
    L1.F = temp;
    temp.clear();
    changes.clear();
    L2.initialState = maxNode;
    for(int i = 0; i < L2.Q.size(); ++i){
        changes[L2.Q[i]] = maxNode++;
        if(L2.F[L2.Q[i]])
        {
            L2.F[L2.Q[i]] = false;
            temp[changes[L2.Q[i]]] = true;
        }
    }
    L2.transitionNormalisation(changes);
    for(int i = 0; i < L2.Q.size(); ++i){
        L2.Q[i] = changes[L2.Q[i]];
    }
    L2.F = temp;
}

LambdaNFA LambdaNFA::unions(LambdaNFA& L1, LambdaNFA& L2){
    LambdaNFA L;
    LambdaNFA::normalisation(L, L1);
    for(int i = 0; i < L1.Q.size(); ++i){
        if(std::find(L.Q.begin(), L.Q.end(), L1.Q[i]) == L.Q.end())
            L.Q.push_back(L1.Q[i]);
        L.transition[L1.Q[i]] = L1.transition[L1.Q[i]];
        try {
            if (L1.F[L1.Q[i]])
                L.F[L1.Q[i]] = true;
        }
        catch(std::out_of_range&){}
    }
    L.addTransition(L.initialState, '#', L1.initialState);
    LambdaNFA::normalisation(L, L2);
    for(int i = 0; i < L2.Q.size(); ++i){
        if(std::find(L.Q.begin(), L.Q.end(), L2.Q[i]) == L.Q.end())
            L.Q.push_back(L2.Q[i]);
        L.transition[L2.Q[i]] = L2.transition[L2.Q[i]];
        try {
            if (L2.F[L2.Q[i]])
                L.F[L2.Q[i]] = true;
        }
        catch(std::out_of_range&){}
    }
    L.addTransition(L.initialState, '#', L2.initialState);
    std::cout << L;
    return L;
}

LambdaNFA LambdaNFA::concatenation(LambdaNFA& L1, LambdaNFA& L2){
    LambdaNFA::normalisation(L1, L2);
    LambdaNFA L = L1;
    for(int i = 0; i < L.Q.size(); ++i)
    {
        try{
            if(L.F[L.Q[i]]) {
                L.F[L.Q[i]] = false;
                L.addTransition(L.Q[i], '#', L2.initialState);
            }
        }
        catch(std::out_of_range&){}
    }
    for(int i = 0; i < L2.Q.size(); ++i) {
        if (!L2.transition[L2.Q[i]].empty())
            L.transition[L2.Q[i]] = L2.transition[L2.Q[i]];
        try{
            if(L2.F[L2.Q[i]])
                L.F[L2.Q[i]] = true;
        }catch(std::out_of_range&){}
        if(std::find(L.Q.begin(), L.Q.end(), L2.Q[i]) == L.Q.end())
            L.Q.push_back(L2.Q[i]);
    }
    return L;
}

LambdaNFA LambdaNFA::star(LambdaNFA& L1){
    LambdaNFA L;
    LambdaNFA::normalisation(L, L1);
    L.addTransition(L.initialState, '#', L1.initialState);
    L.addFinalState(L.initialState, true);
    for(int i = 0; i < L1.Q.size(); ++i){
        if(std::find(L.Q.begin(), L.Q.end(), L1.Q[i]) == L.Q.end())
            L.Q.push_back(L1.Q[i]);
        L.transition[L1.Q[i]] = L1.transition[L1.Q[i]];
        try{
            if(L1.F[L1.Q[i]]){
                L.F[L1.Q[i]] = true;
                L.addTransition(L1.Q[i], '#', L.initialState);
            }
        }catch(std::out_of_range&){}
    }
    return L;
}