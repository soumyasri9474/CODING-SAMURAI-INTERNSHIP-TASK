#include <iostream>
#include <vector>
#include <limits>
using namespace std;

const int BOARD_SIZE = 3;
char board[BOARD_SIZE][BOARD_SIZE] = {
    {' ', ' ', ' '},
    {' ', ' ', ' '},
    {' ', ' ', ' '}
};

// Function to print the board
void printBoard() {
    cout << "-------------\n";
    for (int i = 0; i < BOARD_SIZE; i++) {
        cout << "| ";
        for (int j = 0; j < BOARD_SIZE; j++) {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }
}

// Function to check if the game has a winner
char checkWinner() {
    // Check rows and columns
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
            return board[0][i];
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
        return board[0][2];

    return ' ';
}

// Function to check if the board is full (draw)
bool isBoardFull() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

// Minimax function to determine the best move for the AI
int minimax(int depth, bool isMaximizingPlayer) {
    char winner = checkWinner();
    if (winner == 'X') return -10; // User wins
    if (winner == 'O') return 10;  // AI wins
    if (isBoardFull()) return 0;   // Draw

    if (isMaximizingPlayer) {
        int best = numeric_limits<int>::min(); // Negative infinity
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'O'; // AI move
                    best = max(best, minimax(depth + 1, false));
                    board[i][j] = ' '; // Undo move
                }
            }
        }
        return best;
    } else {
        int best = numeric_limits<int>::max(); // Positive infinity
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = 'X'; // User move
                    best = min(best, minimax(depth + 1, true));
                    board[i][j] = ' '; // Undo move
                }
            }
        }
        return best;
    }
}

// Function to find the best move for the AI
void bestMove() {
    int bestVal = numeric_limits<int>::min();
    int moveRow = -1, moveCol = -1;

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O'; // AI move
                int moveVal = minimax(0, false);
                board[i][j] = ' '; // Undo move

                if (moveVal > bestVal) {
                    moveRow = i;
                    moveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    board[moveRow][moveCol] = 'O'; // AI makes the best move
}

// Function to take user input
void userMove() {
    int row, col;
    while (true) {
        cout << "Enter your move (row and column): ";
        cin >> row >> col;
        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && board[row][col] == ' ') {
            board[row][col] = 'X'; // User move
            break;
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }
}

// Main game loop
int main() {
    while (true) {
        printBoard();

        if (checkWinner() != ' ' || isBoardFull()) {
            break;
        }

        // User's turn
        userMove();
        if (checkWinner() != ' ' || isBoardFull()) {
            break;
        }

        // AI's turn
        bestMove();
        if (checkWinner() != ' ' || isBoardFull()) {
            break;
        }
    }

    printBoard();
    char winner = checkWinner();
    if (winner == 'X') {
        cout << "You win!\n";
    } else if (winner == 'O') {
        cout << "AI wins!\n";
    } else {
        cout << "It's a draw!\n";
    }

    return 0;
}
