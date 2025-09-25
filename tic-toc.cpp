#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

char board[3][3]; 

void initializeBoard() {
    char pos = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = pos++;
        }
    }
}

void displayBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "------------\n";
    }
    cout << "\n";
}

bool checkWin(char player) {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    }
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

bool checkDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

bool playerMove(char player) {
    int move;
    cout << "Player " << player << ", enter your move (1-9): ";
    cin >> move;

    if (move < 1 || move > 9) return false;

    int row = (move - 1) / 3;
    int col = (move - 1) % 3;

    if (board[row][col] == 'X' || board[row][col] == 'O') return false;

    board[row][col] = player;
    return true;
}

void aiMove() {
    for (int i = 1; i <= 9; i++) {
        int row = (i - 1) / 3, col = (i - 1) % 3;
        if (board[row][col] != 'X' && board[row][col] != 'O') {
            char backup = board[row][col];
            board[row][col] = 'O';
            if (checkWin('O')) return;
            board[row][col] = backup;
        }
    }

    for (int i = 1; i <= 9; i++) {
        int row = (i - 1) / 3, col = (i - 1) % 3;
        if (board[row][col] != 'X' && board[row][col] != 'O') {
            char backup = board[row][col];
            board[row][col] = 'X';
            if (checkWin('X')) {
                board[row][col] = 'O';
                return;
            }
            board[row][col] = backup;
        }
    }
    vector<int> available;
    for (int i = 1; i <= 9; i++) {
        int row = (i - 1) / 3, col = (i - 1) % 3;
        if (board[row][col] != 'X' && board[row][col] != 'O') {
            available.push_back(i);
        }
    }
    if (!available.empty()) {
        int move = available[rand() % available.size()];
        int row = (move - 1) / 3, col = (move - 1) % 3;
        board[row][col] = 'O';
    }
}

int main() {
    srand(time(0));
    int mode;
    cout << "---- Tic-Tac-Toe Game ----\n";
    cout << "1. Player vs Player\n2. Player vs Computer\nChoose mode: ";
    cin >> mode;

    initializeBoard();
    displayBoard();

    char currentPlayer = 'You';
    bool gameOver = false;

    while (!gameOver) {
        bool validMove = false;

        if (mode == 1 || (mode == 2 && currentPlayer == 'You')) {
            validMove = playerMove(currentPlayer);
        } else {
            cout << "Computer (O) is making a move...\n";
            aiMove();
            validMove = true;
        }

        if (!validMove) {
            cout << "Already Taken This Move.\n";
            continue;
        }

        displayBoard();

        if (checkWin(currentPlayer)) {
            cout << "woooow Player " << currentPlayer << " wins!\n";
            gameOver = true;
        } else if (checkDraw()) {
            cout << " Opps! It's a draw!\n";
            gameOver = true;
        }

        currentPlayer = (currentPlayer == 'You') ? 'O' : 'You';
    }
    return 0;
}
