#include <iostream>
#include <fstream>
#include <string>
using namespace std;


void sendMessage(const string &username, const string &message) {
    ofstream chatFile("chat.txt", ios::app); 
    if (!chatFile) {
        cout << "Error: Could not open chat.txt\n";
        return;
    }
    chatFile << username << ": " << message << "\n";
    chatFile.close();
}


void showChat() {
    ifstream chatFile("chat.txt");
    if (!chatFile) {
        cout << "No chat history yet.\n";
        return;
    }
    string line;
    cout << "\n=== Chat History ===\n";
    while (getline(chatFile, line)) {
        cout << line << endl;
    }
    cout << "====================\n";
    chatFile.close();
}

int main() {
    string user1, user2;
    cout << "Enter name for User 1: ";
    cin >> user1;
    cout << "Enter name for User 2: ";
    cin >> user2;

    int choice;
    string message, sender;

    do {
        cout << "\n   Mini Chat App   \n";
        cout << "1. " << user1 << " send message\n";
        cout << "2. " << user2 << " send message\n";
        cout << "3. Show Chat History\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); 
        switch (choice) {
            case 1:
                cout << user1 << ": ";
                getline(cin, message);
                sendMessage(user1, message);
                break;
            case 2:
                cout << user2 << ": ";
                getline(cin, message);
                sendMessage(user2, message);
                break;
            case 3:
                showChat();
                break;
            case 4:
                cout << "Exiting chat...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
