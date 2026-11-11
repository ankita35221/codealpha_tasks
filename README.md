# Task 1: CGPA Calculator

## Features
- Accepts course names, grade points (0–10), and credit hours.
- Calculates semester GPA using the weighted-grade formula.
- Calculates cumulative CGPA using previous CGPA and previously completed credits.
- Displays each course and the final results.
- Validates grade points, credits, and course count.

## Formula
- Semester GPA = Sum(Grade Point × Credit Hours) / Sum(Credit Hours)
- Overall CGPA = (Previous CGPA × Previous Credits + Current Semester Grade Points) / Total Credits

For the first semester, enter `0` for previous CGPA and previous credits.

## Compile and run
```bash
g++ -std=c++17 main.cpp -o cgpa
./cgpa
```
On Windows:
```bash
g++ -std=c++17 main.cpp -o cgpa.exe
cgpa.exe
```
