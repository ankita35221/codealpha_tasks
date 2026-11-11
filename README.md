# Task 3: Sudoku Solver

## Features
- Stores the puzzle in a 9×9 two-dimensional array.
- Accepts user input; use `0` for empty cells.
- Checks row, column, and 3×3 subgrid constraints.
- Uses recursive backtracking to find a solution.
- Reports invalid or unsolvable puzzles.

## Compile and run
```bash
g++ -std=c++17 main.cpp -o sudoku
./sudoku
```
On Windows:
```bash
g++ -std=c++17 main.cpp -o sudoku.exe
sudoku.exe
```

Enter 9 rows, with 9 integers per row, separated by spaces.
