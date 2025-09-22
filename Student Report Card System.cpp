#include <iostream>
#include <string>
using namespace std;


char calculateGrade(float percentage) {
    if (percentage >= 90) return 'A';
    else if (percentage >= 75) return 'B';
    else if (percentage >= 60) return 'C';
    else if (percentage >= 50) return 'D';
    else return 'F';
}

int main() {
    string Name;
    int RollNo;
    int Subjects;

    cout << "[      Student Report Card System     ]" << endl;


    cout << "Enter Student Name: ";
    getline(cin, Name);

    cout << "Enter Roll Number: ";
    cin >> RollNo;

    cout << "Enter number of subjects: ";
    cin >> Subjects;

    int marks[100];
    int totalMarks = 0;

    for (int i = 0; i < Subjects; i++) {
        cout << "Enter marks of subject " << i + 1 << " (out of 100): ";
        cin >> marks[i];
        totalMarks += marks[i];
    }

    float percentage = (float)totalMarks / Subjects;
    char grade = calculateGrade(percentage);

    cout << "\n-------- Report Card --------" << endl;
    cout << "Name: " << Name << endl;
    cout << "Roll Number: " << RollNo << endl;
    cout << "-----------------------------" << endl;

    for (int i = 0; i < Subjects; i++) {
        cout << "Subject " << i + 1 << " Marks: " << marks[i] << endl;
    }

    cout << "-----------------------------" << endl;
    cout << "Total Marks: " << totalMarks << "/" << Subjects * 100 << endl;
    cout << "Percentage: " << percentage << "%" << endl;
    cout << "Grade: " << grade << endl;
    cout << "------------------------------" << endl;

    return 0;
}

