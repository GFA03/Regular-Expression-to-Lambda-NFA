#include <#-nfa.h>
#include <fstream>
#include <sstream>

LambdaNFA::LambdaNFA(int initialState = 0){
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
    int num_elements = sizeof(obj.Q) / sizeof(obj.Q[0]);
    out << "Automata nodes:";
    for(int i = 0; i < num_elements; ++i)
    {
        if(!obj.Q[i].empty())
            out << " " << i;
    }
    out << '\n';
    out << "Initial state: " << obj.initialState << '\n';
    out << "Final states:";
    for(int i = 0; i < num_elements; ++i)
    {
        if(obj.F.at(i) == true)
            out << " " << i;
    }
    return out;
}

void LambdaNFA::addTransition(int startState, std::string letter, int endState){
    Q[startState][letter].insert(endState);    
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

void LambdaNFA::depthSearch(std::vector<int> &path, std::unordered_set<int> currentState, int depth, std::string word){
    std::unordered_set<int> temp;
    // for(auto state: currentState)
    //     std::cout << state << " ";
    // std::cout << '\n';
    for(auto state: currentState)
    {
        // this->Q[1]['a'] = {1}; TEST TEST TEST
        // temp.insert(this->Q[state][word[depth]].begin(),this->Q[state][word[depth]].end());
        path[depth] = state;
        if(depth <= word.length())
        {
            if(depth == word.length())
            {
                // std::cout << "depth: " << depth << " vector: ";
                // for(auto elem: path)
                //     std::cout << elem << " ";
                // std::cout << '\n';
                if(this->F[path.back() == true])
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

int main(){

    return 0;
}