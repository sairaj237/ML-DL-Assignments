#include <iostream>
#include <string>
using namespace std;

string respond(string input){
    if(input=="hi" || input=="hello") return "Hello! How can I help you?";
    if(input=="how are you?") return "I'm fine, thank you!";
    if(input=="bye") return "Goodbye!";
    return "Sorry, I don't understand.";
}

int main(){
    string input;
    cout << "Chatbot: Hello! Type 'bye' to exit.\n";
    while(true){
        cout << "You: ";
        getline(cin, input);
        if(input=="bye") {
            cout << "Chatbot: Goodbye!\n";
            break;
        }
        cout << "Chatbot: " << respond(input) << "\n";
    }
}
