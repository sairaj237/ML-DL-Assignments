#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Rule {
    vector<string> premises;
    string conclusion;
};

bool forwardChaining(vector<Rule> rules, vector<string> facts, string query){
    vector<string> inferred;
    bool added;
    do{
        added = false;
        for(auto r: rules){
            bool canInfer = true;
            for(auto p: r.premises)
                if(find(facts.begin(), facts.end(), p) == facts.end())
                    canInfer = false;
            if(canInfer && find(facts.begin(), facts.end(), r.conclusion) == facts.end()){
                facts.push_back(r.conclusion);
                added = true;
            }
        }
    } while(added);

    return find(facts.begin(), facts.end(), query) != facts.end();
}

int main(){
    vector<string> facts = {"A", "B"};
    vector<Rule> rules = {
        {{"A","B"}, "C"},
        {{"C"}, "D"},
        {{"B"}, "E"}
    };
    string query = "D";
    if(forwardChaining(rules,facts,query))
        cout << "Yes, " << query << " can be inferred\n";
    else
        cout << "No, " << query << " cannot be inferred\n";
}
