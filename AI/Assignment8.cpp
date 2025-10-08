#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Rule {
    vector<string> premises;
    string conclusion;
};

bool backwardChaining(vector<Rule> rules, vector<string> facts, string query){
    if(find(facts.begin(), facts.end(), query) != facts.end()) return true;
    for(auto r: rules){
        if(r.conclusion == query){
            bool canInfer = true;
            for(auto p: r.premises){
                if(!backwardChaining(rules,facts,p)){
                    canInfer = false;
                    break;
                }
            }
            if(canInfer) return true;
        }
    }
    return false;
}

int main(){
    vector<string> facts = {"A","B"};
    vector<Rule> rules = {
        {{"A","B"}, "C"},
        {{"C"}, "D"},
        {{"B"}, "E"}
    };
    string query = "D";
    if(backwardChaining(rules,facts,query))
        cout << "Yes, " << query << " can be inferred\n";
    else
        cout << "No, " << query << " cannot be inferred\n";
}
