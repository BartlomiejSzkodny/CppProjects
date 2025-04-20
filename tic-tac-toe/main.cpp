#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main(){
    std::cout << "Welcome to Tic Tac Toe!" << std::endl;
    char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    char currentPlayer = 'X';
    int choice;
    int row, col;
    bool draw = false;

    while (true) {
        std::cout << "Current board:" << std::endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                std::cout << board[i][j] << " ";
            }
            std::cout << std::endl;
        }


        std::cout << "Player " << currentPlayer << ", enter your choice (1-9): ";
        std::cin >> choice;


        row = (choice - 1) / 3;
        col = (choice - 1) % 3;

        if (board[row][col] != 'X' && board[row][col] != 'O') {
            board[row][col] = currentPlayer;
            if ((board[0][col] == currentPlayer && board[1][col] == currentPlayer && board[2][col] == currentPlayer) ||
                (board[row][0] == currentPlayer && board[row][1] == currentPlayer && board[row][2] == currentPlayer) ||
                (row == col && board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
                (row + col == 2 && board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) {
                std::cout << "Player " << currentPlayer << " wins!" << std::endl;
                break;
            }
        } else {
            std::cout << "Cell already occupied! Try again." << std::endl;
            continue;
        }

        // Check for draw condition
        draw = true;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != 'X' && board[i][j] != 'O') {
                    draw = false;
                    break;
                }
            }
        }
        if (draw) {
            std::cout << "It's a draw!" << std::endl;
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';

    }
}