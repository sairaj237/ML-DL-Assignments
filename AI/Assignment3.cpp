#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

map<string, vector<string>> parentToChildren;
map<string, vector<string>> childToParent;

void addRelation(string parent, string child) {
    parentToChildren[parent].push_back(child); 
    childToParent[child].push_back(parent); 
}

void showChildren(string parent) {
    if (parentToChildren.find(parent) != parentToChildren.end()) {
        cout << "Children of " << parent << ": ";
        for (string child : parentToChildren[parent]) {
            cout << child << " ";
        }
        cout << endl;   
    } else {
        cout << parent << " has no recorded children in the knowledge base.\n";       
    }
}


void showParent(string child) {
    if (childToParent.find(child) != childToParent.end()) {
        cout <<"Parents of " << child << ": ";
        for(string parent : childToParent[child]) {
            cout << parent << " ";
        }
        cout << endl;
    } else {
        cout << "Parent of " << child << " not found in the knowledge base.\n";     
    }
}

bool isCousin(string person1, string person2) {
    if (childToParent.find(person1) == childToParent.end() || 
        childToParent.find(person2) == childToParent.end()) {
        return false; 
    }

    if(person1 == person2) return false;

    for (string parent1 : childToParent[person1]) {
        for (string parent2 : childToParent[person2]) {
            if (parent1 != parent2 && 
                childToParent.find(parent1) != childToParent.end() && 
                childToParent.find(parent2) != childToParent.end()) {
                for (string gp1 : childToParent[parent1]) {
                    for (string gp2 : childToParent[parent2]) {
                        if (gp1 == gp2) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void showSpouse(string person) {

    if (parentToChildren.find(person) == parentToChildren.end()) {
        cout << person << " has no recorded spouse in the knowledge base.\n";
        return;
    }

    for (string child : parentToChildren[person]) {
        if (childToParent.find(child) != childToParent.end()) {
            for (string parent : childToParent[child]) {
                if (parent != person) {
                    cout << "Spouse of " << person << " is: " << parent << endl;
                    return;
                }
            }
        }
    }

    cout << person << " has no recorded spouse in the knowledge base.\n";
}

int main() {
    int choice;
    string parent, child, name, person1, person2;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add parent-child relation\n";    
        cout << "2. Show children of a person\n";
        cout << "3. Show parent of a person\n";
        cout << "4. Show spouse of a person\n";
        cout << "5. Check if two persons are cousins\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter parent name: ";
            cin >> parent;
            cout << "Enter child name: ";
            cin >> child;
            addRelation(parent, child);
            cout << "Relation added!\n";
            break;

        case 2:
            cout << "Enter name to find children: ";
            cin >> name;
            showChildren(name);
            break;

        case 3:
            cout << "Enter name to find parent: ";
            cin >> name;
            showParent(name);
            break;

        case 4:
            cout << "Enter name to find spouse: ";
            cin >> name;
            showSpouse(name);
            break;

        case 5:
            cout << "Enter first person: ";
            cin >> person1;
            cout << "Enter second person: ";
            cin >> person2;
            if (isCousin(person1, person2))
                cout << person1 << " and " << person2 << " are cousins.\n";
            else
                cout << person1 << " and " << person2 << " are NOT cousins.\n";
            break;

        case 6:
            cout << "Exiting program\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}
