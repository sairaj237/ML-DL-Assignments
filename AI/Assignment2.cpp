#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Variables: regions of the map
vector<string> variables = {"WA", "NT", "SA", "Q", "NSW", "V", "T"};

// Domains: colors available
vector<string> colors = {"Red", "Green", "Blue"};
map<string, vector<string>> domains;

// Neighbors: adjacency constraints
map<string, vector<string>> neighbors = {
    {"WA", {"NT", "SA"}},
    {"NT", {"WA", "SA", "Q"}},
    {"SA", {"WA", "NT", "Q", "NSW", "V"}},
    {"Q", {"NT", "SA", "NSW"}},
    {"NSW", {"Q", "SA", "V"}},
    {"V", {"SA", "NSW"}},
    {"T", {}}
};

// Function to check if the assignment is consistent
bool isConsistent(string var, string value, map<string, string> &assignment) {
    for (auto neighbor : neighbors[var]) {
        if (assignment.find(neighbor) != assignment.end() && assignment[neighbor] == value) {
            return false;
        }
    }
    return true;
}

// Backtracking search
bool backtrack(map<string, string> &assignment) {
    // If assignment is complete
    if (assignment.size() == variables.size())
        return true;

    // Select unassigned variable
    string var;
    for (auto v : variables) {
        if (assignment.find(v) == assignment.end()) {
            var = v;
            break;
        }
    }

    for (auto value : domains[var]) {
        if (isConsistent(var, value, assignment)) {
            assignment[var] = value;
            if (backtrack(assignment))
                return true;
            // Remove assignment and backtrack
            assignment.erase(var);
        }
    }

    return false;
}

int main() {
    // Initialize domains
    for (auto var : variables)
        domains[var] = colors;

    map<string, string> assignment;

    if (backtrack(assignment)) {
        cout << "Solution found:\n";
        for (auto kv : assignment)
            cout << kv.first << " : " << kv.second << endl;
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}
