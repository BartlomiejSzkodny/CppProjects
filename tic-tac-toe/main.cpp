#include <iostream>
#include <conio.h> // For _getch() and _kbhit()
#include <windows.h> // For system("cls")

void printBoard(char board[3][3], int cursorRow, int cursorCol) {
    system("cls"); // Clear the console
    std::cout << "Use arrow keys to move and press Enter to select.\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == cursorRow && j == cursorCol) {
                std::cout << "[" << board[i][j] << "] ";
            } else {
                std::cout << " " << board[i][j] << "  ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    std::cout << "Welcome to Tic Tac Toe!" << std::endl;
    char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    char currentPlayer = 'X';
    int cursorRow = 0, cursorCol = 0;
    bool draw = false;

    while (true) {
        printBoard(board, cursorRow, cursorCol);

        int key = _getch(); // Get user input
        if (key == 224) { // Arrow keys are preceded by 224
            key = _getch();
            switch (key) {
                case 72: // Up arrow
                    cursorRow = (cursorRow > 0) ? cursorRow - 1 : 2;
                    break;
                case 80: // Down arrow
                    cursorRow = (cursorRow < 2) ? cursorRow + 1 : 0;
                    break;
                case 75: // Left arrow
                    cursorCol = (cursorCol > 0) ? cursorCol - 1 : 2;
                    break;
                case 77: // Right arrow
                    cursorCol = (cursorCol < 2) ? cursorCol + 1 : 0;
                    break;
            }
        } else if (key == 13) { // Enter key
            if (board[cursorRow][cursorCol] != 'X' && board[cursorRow][cursorCol] != 'O') {
                board[cursorRow][cursorCol] = currentPlayer;

                // Check for win condition
                if ((board[0][cursorCol] == currentPlayer && board[1][cursorCol] == currentPlayer && board[2][cursorCol] == currentPlayer) ||
                    (board[cursorRow][0] == currentPlayer && board[cursorRow][1] == currentPlayer && board[cursorRow][2] == currentPlayer) ||
                    (cursorRow == cursorCol && board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
                    (cursorRow + cursorCol == 2 && board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer)) {
                    printBoard(board, cursorRow, cursorCol);
                    std::cout << "Player " << currentPlayer << " wins!" << std::endl;
                    break;
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
                    printBoard(board, cursorRow, cursorCol);
                    std::cout << "It's a draw!" << std::endl;
                    break;
                }

                currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
            } else {
                std::cout << "Cell already occupied! Try again." << std::endl;
                Sleep(1000); // Pause for 1 second
            }
        }
    }

    return 0;
}