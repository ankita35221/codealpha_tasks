#include <iostream>
using namespace std;

const int SIZE = 9;

void printGrid(int grid[SIZE][SIZE]) {
    cout << "\n+-------+-------+-------+\n";
    for (int row = 0; row < SIZE; row++) {
        cout << "| ";
        for (int col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0)
                cout << ". ";
            else
                cout << grid[row][col] << ' ';

            if ((col + 1) % 3 == 0)
                cout << "| ";
        }
        cout << '\n';
        if ((row + 1) % 3 == 0)
            cout << "+-------+-------+-------+\n";
    }
}

bool isSafe(int grid[SIZE][SIZE], int row, int col, int number) {
    // Check the complete row and column.
    for (int i = 0; i < SIZE; i++) {
        if (grid[row][i] == number || grid[i][col] == number)
            return false;
    }

    // Find the top-left corner of the 3x3 subgrid.
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int r = startRow; r < startRow + 3; r++) {
        for (int c = startCol; c < startCol + 3; c++) {
            if (grid[r][c] == number)
                return false;
        }
    }
    return true;
}

bool solveSudoku(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (grid[row][col] == 0) {
                for (int number = 1; number <= 9; number++) {
                    if (isSafe(grid, row, col, number)) {
                        grid[row][col] = number;

                        if (solveSudoku(grid))
                            return true;

                        // Backtrack if this number does not lead to a solution.
                        grid[row][col] = 0;
                    }
                }
                return false; // No valid number fits this empty cell.
            }
        }
    }
    return true; // No empty cells remain.
}

bool isInitialGridValid(int grid[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            int number = grid[row][col];
            if (number < 0 || number > 9)
                return false;

            if (number != 0) {
                grid[row][col] = 0;
                bool valid = isSafe(grid, row, col, number);
                grid[row][col] = number;
                if (!valid)
                    return false;
            }
        }
    }
    return true;
}

int main() {
    int grid[SIZE][SIZE];

    cout << "========== SUDOKU SOLVER ==========\n";
    cout << "Enter the Sudoku puzzle row by row.\n";
    cout << "Use 0 for an empty cell. Enter 9 numbers in each row.\n\n";

    for (int row = 0; row < SIZE; row++) {
        cout << "Enter row " << row + 1 << " (9 numbers separated by spaces): ";
        for (int col = 0; col < SIZE; col++) {
            cin >> grid[row][col];
            if (cin.fail()) {
                cout << "Invalid input. Please enter integers from 0 to 9.\n";
                return 1;
            }
        }
    }

    if (!isInitialGridValid(grid)) {
        cout << "\nThe entered puzzle contains invalid or repeated numbers.\n";
        return 1;
    }

    cout << "\nOriginal puzzle:";
    printGrid(grid);

    if (solveSudoku(grid)) {
        cout << "\nSolved Sudoku:";
        printGrid(grid);
    } else {
        cout << "\nNo solution exists for the entered Sudoku puzzle.\n";
    }

    return 0;
}
