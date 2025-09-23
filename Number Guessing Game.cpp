#include <iostream>
#include <cstdlib>   // for rand() and srand()
#include <ctime>    
using namespace std;

int main() {
    srand(time(0));               
    int target = rand() % 100 + 1; 
    int guess;
    int attempts = 0;

    cout << "--- Number Guessing Game ----n";
    cout << "Guess the number between 1 and 100\n\n";

    do {
        cout << "Enter your guess: ";
        cin >> guess;
        attempts++;

        if (guess > target) {
            cout << "Too high! Try again.\n";
        } 
        else if (guess < target) {
            cout << "Too low! Try again.\n";
        } 
        else {
            cout << " Correct! You guessed it in " << attempts << " attempts.\n";
        }

    } while (guess != target);

    return 0;
}
