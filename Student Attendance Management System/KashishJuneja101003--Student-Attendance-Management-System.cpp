#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

// Enum for Attendance Status
enum class AttendanceStatus { Present, Absent, Late };

// Convert Enum to String
string statusToString(AttendanceStatus status) {
    switch (status) {
        case AttendanceStatus::Present: return "Present";
        case AttendanceStatus::Absent: return "Absent";
        case AttendanceStatus::Late: return "Late";
        default: return "Unknown";
    }
}

// Student Class
class Student {
public:
    string name;
    int rollNumber;
    string className;
    vector<AttendanceStatus> attendanceRecord;

    Student(string n, int roll, string c) : name(n), rollNumber(roll), className(c) {}

    void markAttendance(AttendanceStatus status) {
        attendanceRecord.push_back(status);
    }

    void viewAttendance() {
        cout << "\nAttendance record for " << name << " (Roll No: " << rollNumber << "):\n";
        if (attendanceRecord.empty()) {
            cout << "No attendance records available.\n";
        } else {
            for (const auto& status : attendanceRecord) {
                cout << statusToString(status) << endl;
            }
        }
    }
};

// Attendance System Class
class AttendanceSystem {
private:
    unordered_map<int, Student*> students;

public:
    ~AttendanceSystem() {
        for (auto& pair : students) {
            delete pair.second;  // Free allocated memory
        }
    }

    void addStudent(string name, int rollNumber, string className) {
        if (students.find(rollNumber) != students.end()) {
            cout << "Student with this roll number already exists!\n";
            return;
        }
        students[rollNumber] = new Student(name, rollNumber, className);
        cout << "Student added successfully!\n";
    }

    void markAttendance(int rollNumber, AttendanceStatus status) {
        if (students.find(rollNumber) != students.end()) {
            students[rollNumber]->markAttendance(status);
            cout << "Attendance marked successfully!\n";
        } else {
            cout << "Student not found!\n";
        }
    }

    void viewAttendance(int rollNumber) {
        if (students.find(rollNumber) != students.end()) {
            students[rollNumber]->viewAttendance();
        } else {
            cout << "Student not found!\n";
        }
    }

    void removeStudent(int rollNumber) {
        auto it = students.find(rollNumber);
        if (it != students.end()) {
            delete it->second;  // Free allocated memory
            students.erase(it);
            cout << "Student removed successfully!\n";
        } else {
            cout << "Student not found!\n";
        }
    }
};

// Function to Handle String Input
string getInputString(const string& prompt) {
    cout << prompt;
    cin.ignore();  // Ignore any leftover newline
    string input;
    getline(cin, input);
    return input;
}

// Main Function
int main() {
    AttendanceSystem system;
    int choice, rollNumber;
    string name, className;
    
    while (true) {
        cout << "\n----- Student Attendance Management System -----\n"
             << "1. Add Student\n"
             << "2. Mark Attendance\n"
             << "3. View Attendance\n"
             << "4. Remove Student\n"
             << "5. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                name = getInputString("Enter student name: ");
                cout << "Enter roll number: ";
                cin >> rollNumber;
                className = getInputString("Enter class name: ");
                system.addStudent(name, rollNumber, className);
                break;

            case 2:
                cout << "Enter roll number: ";
                cin >> rollNumber;
                cout << "Enter attendance status (1: Present, 2: Absent, 3: Late): ";
                int statusInput;
                cin >> statusInput;

                if (statusInput >= 1 && statusInput <= 3) {
                    system.markAttendance(rollNumber, static_cast<AttendanceStatus>(statusInput - 1));
                } else {
                    cout << "Invalid status! Please enter a valid option.\n";
                }
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
}
