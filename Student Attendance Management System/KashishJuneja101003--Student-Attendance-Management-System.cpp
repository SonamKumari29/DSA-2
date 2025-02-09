#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Student {
public:
    string name;
    int rollNumber;
    string className;
    vector<string> attendanceRecord;

    // Default constructor
    Student() : name(""), rollNumber(0), className("") {}

    // Parameterized constructor
    Student(string n, int roll, string c) : name(n), rollNumber(roll), className(c) {}

    void markAttendance(string status) {
        attendanceRecord.push_back(status);
    }

    void viewAttendance() {
        cout << "Attendance record for " << name << " (Roll No: " << rollNumber << "):\n";
        for (const auto& status : attendanceRecord) {
            cout << status << endl;
        }
    }
};

class AttendanceSystem {
private:
    unordered_map<int, Student> students;

public:
    void addStudent(string name, int rollNumber, string className) {
        students[rollNumber] = Student(name, rollNumber, className);
        cout << "Student added successfully!\n";
    }

    void markAttendance(int rollNumber, string status) {
        if (students.find(rollNumber) != students.end()) {
            students[rollNumber].markAttendance(status);
            cout << "Attendance marked successfully!\n";
        } else {
            cout << "Student not found!\n";
        }
    }

    void viewAttendance(int rollNumber) {
        if (students.find(rollNumber) != students.end()) {
            students[rollNumber].viewAttendance();
        } else {
            cout << "Student not found!\n";
        }
    }

    void removeStudent(int rollNumber) {
        if (students.erase(rollNumber)) {
            cout << "Student removed successfully!\n";
        } else {
            cout << "Student not found!\n";
        }
    }
};

int main() {
    AttendanceSystem system;
    int choice;
    int rollNumber;
    string name, className, status;

    while (true) {
        cout << "\n----- Student Attendance Management System -----\n";
        cout << "1. Add Student\n";
        cout << "2. Mark Attendance\n";
        cout << "3. View Attendance\n";
        cout << "4. Remove Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter roll number: ";
                cin >> rollNumber;
                cout << "Enter class name: ";
                cin.ignore();
                getline(cin, className);
                system.addStudent(name, rollNumber, className);
                break;

            case 2:
                cout << "Enter roll number: ";
                cin >> rollNumber;
                cout << "Enter attendance status (Present, Absent, Late): ";
                cin.ignore();
                getline(cin, status);
                system.markAttendance(rollNumber, status);
                break;

            case 3:
                cout << "Enter roll number: ";
                cin >> rollNumber;
                system.viewAttendance(rollNumber);
                break;

            case 4:
                cout << "Enter roll number: ";
                cin >> rollNumber;
                system.removeStudent(rollNumber);
                break;

            case 5:
                cout << "Exiting the system.\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
