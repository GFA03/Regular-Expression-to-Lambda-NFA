#include "lambda-nfa.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

LambdaNFA::LambdaNFA(int initialState){
    this->initialState = initialState;
}

LambdaNFA::LambdaNFA(const LambdaNFA& obj){
    this->initialState = obj.initialState;
}

LambdaNFA& LambdaNFA::operator=(const LambdaNFA& obj){
    if(this != &obj){
        this->initialState = obj.initialState;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const LambdaNFA& obj){
    out << "Automata nodes:";
    for(int i = 0; i < obj.Q.size(); ++i)
    {
        out << obj.Q[i] << " ";
    }
    out << '\n';
    out << "Initial state: " << obj.initialState << '\n';
    out << "Final states:";
    for(int i = 0; i < obj.Q.size(); ++i)
    {
        if(obj.F.at(i) == true)
            out << " " << i;
    }
    return out;
}

void LambdaNFA::addTransition(int startState, std::string letter, int endState){
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
}

void LambdaNFA::addFinalState(int finalState, bool final){
    F[finalState] = final;
}

void LambdaNFA::readFromFile(const std::string& filename)
{
    std::ifstream f1(filename);
    f1 >> this->initialState;
    int temp, node1, node2;
    std::string letter;
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
        tempStates = transition[state]["#"];
        for(auto elem: tempStates)
        {
            if(std::find(currentStates.begin(), currentStates.end(), elem) == currentStates.end())
                allEquals = false;
        }
        if(allEquals == false)
            lambda_paths(currentStates, this->transition[state]["#"]);
    }
}

void LambdaNFA::depthSearch(std::vector<int> &path, std::unordered_set<int> currentState, int depth, std::string word){
    std::unordered_set<int> temp;
    // for(auto state: currentState)
    //     std::cout << state << " ";
    // std::cout << '\n';
    lambda_paths(currentState, currentState);
    for(auto state: currentState)
    {
        std::string tempString = word.substr(depth, depth+1);
        temp.insert(this->transition[state][tempString].begin(),this->transition[state][tempString].end());
        lambda_paths(temp, temp);
        path[depth] = state;
        if(depth <= word.length())
        {
            if(depth == word.length())
            {
                // std::cout << "depth: " << depth << " vector: ";
                // for(auto elem: path)
                //     std::cout << elem << " ";
                // std::cout << '\n';
                if(this->F[path.back()] == true)
                    this->result[k++] = path;
            }
            else{
                // std::cout << "depth: " << depth << " vector: ";
                // for(auto elem: path)
                //     std::cout << elem << " ";
                // std::cout << '\n';
                depthSearch(path, temp, depth+1, word);
            }
        temp.clear();
        }
    }
}

void LambdaNFA::printPaths(){
    int i = 0;
    while(!result[i].empty())
        {   
            for(auto elem: result[i])
                std:: cout << elem << " ";
            std::cout << '\n';
            i++;
        }
}

int main(){
    LambdaNFA obj;
    // obj.addTransition(0, "#", 2);
    // obj.addTransition(0, "1", 1);
    // obj.addTransition(0, "2", 3);
    // obj.addTransition(1, "1", 0);
    // obj.addTransition(2, "#", 0);
    // obj.addTransition(2, "0", 4);
    // obj.addTransition(2, "2", 3);
    // obj.addTransition(3, "2", 0);
    // obj.addTransition(3, "2", 2);
    // obj.addTransition(4, "0", 2);
    // obj.addFinalState(2, 1);
    // obj.addFinalState(0, 1);

    
    obj.addTransition(0, "#", 1);
    obj.addTransition(0, "b", 1);
    obj.addTransition(0, "#", 3);
    obj.addTransition(1, "b", 2);
    obj.addTransition(2, "a", 1);
    obj.addTransition(3, "b", 0);
    obj.addTransition(3, "#", 1);
    obj.addTransition(3, "#", 2);
    obj.addTransition(3, "a", 4);
    obj.addTransition(3, "a", 3);
    obj.addTransition(4, "#", 2);
    obj.addTransition(4, "b", 4);
    obj.addTransition(4, "b", 3);
    obj.addFinalState(0, 1);

    std::vector<int> path;
    path.assign(6, -1);
    obj.depthSearch(path, {0}, 0, "aababb");
    obj.printPaths();
    // std::unordered_set<int> temp = {0};
    // obj.lambda_paths(temp, temp);
    // for(auto elem: temp)
    //     std::cout << elem << " ";
    return 0;
}