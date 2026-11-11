#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <string>
using namespace std;

struct Course {
    string name;
    double gradePoint;
    double creditHours;
};

int main() {
    int numberOfCourses;
    cout << "===== CGPA CALCULATOR =====\n";
    cout << "Enter number of courses this semester: ";
    cin >> numberOfCourses;

    while (cin.fail() || numberOfCourses <= 0) {
        cout << "Please enter a valid positive number of courses: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> numberOfCourses;
    }

    vector<Course> courses;
    double semesterGradePoints = 0.0;
    double semesterCredits = 0.0;

    for (int i = 0; i < numberOfCourses; i++) {
        Course course;

        cout << "\nCourse " << i + 1 << " name (use _ instead of spaces): ";
        cin >> course.name;

        cout << "Enter grade point (0 to 10): ";
        cin >> course.gradePoint;
        while (cin.fail() || course.gradePoint < 0 || course.gradePoint > 10) {
            cout << "Invalid grade. Enter a value from 0 to 10: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> course.gradePoint;
        }

        cout << "Enter credit hours (greater than 0): ";
        cin >> course.creditHours;
        while (cin.fail() || course.creditHours <= 0) {
            cout << "Invalid credits. Enter a value greater than 0: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> course.creditHours;
        }

        semesterGradePoints += course.gradePoint * course.creditHours;
        semesterCredits += course.creditHours;
        courses.push_back(course);
    }

    double semesterGPA = semesterGradePoints / semesterCredits;

    // Previous CGPA is needed to calculate cumulative CGPA correctly.
    double previousCGPA, previousCredits;
    cout << "\nEnter previous CGPA (enter 0 if this is your first semester): ";
    cin >> previousCGPA;
    while (cin.fail() || previousCGPA < 0 || previousCGPA > 10) {
        cout << "Enter a valid previous CGPA from 0 to 10: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> previousCGPA;
    }

    cout << "Enter total credits completed before this semester (0 for first semester): ";
    cin >> previousCredits;
    while (cin.fail() || previousCredits < 0) {
        cout << "Enter valid non-negative previous credits: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> previousCredits;
    }

    if (previousCredits == 0) {
        previousCGPA = 0; // Ignore a previous CGPA when no previous credits exist.
    }

    double cumulativeCredits = previousCredits + semesterCredits;
    double cumulativeGradePoints =
        (previousCGPA * previousCredits) + semesterGradePoints;
    double cgpa = cumulativeGradePoints / cumulativeCredits;

    cout << "\n========== RESULT ==========\n";
    cout << left << setw(22) << "Course"
         << setw(16) << "Grade Point" << "Credits\n";
    cout << "---------------------------------------------\n";

    for (const Course& course : courses) {
        cout << left << setw(22) << course.name
             << setw(16) << fixed << setprecision(2) << course.gradePoint
             << course.creditHours << '\n';
    }

    cout << "\nSemester GPA : " << fixed << setprecision(2) << semesterGPA;
    cout << "\nOverall CGPA : " << fixed << setprecision(2) << cgpa;
    cout << "\nTotal Credits: " << cumulativeCredits << '\n';

    return 0;
}
