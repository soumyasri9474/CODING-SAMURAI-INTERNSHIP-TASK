#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student {
    string name;
    int rollNumber;
    float marks;
};

const int MAX_STUDENTS = 100;
Student students[MAX_STUDENTS];
int studentCount = 0;

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        cout << "Maximum student limit reached." << endl;
        return;
    }

    Student newStudent;
    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, newStudent.name);
    cout << "Enter roll number: ";
    cin >> newStudent.rollNumber;
    cout << "Enter marks: ";
    cin >> newStudent.marks;

    students[studentCount++] = newStudent;
    cout << "Student added successfully!" << endl;
}

void displayStudents() {
    if (studentCount == 0) {
        cout << "No students to display." << endl;
        return;
    }

    cout << "\nStudent List:" << endl;
    for (int i = 0; i < studentCount; ++i) {
        cout << "Name: " << students[i].name << ", Roll Number: " << students[i].rollNumber << ", Marks: " << students[i].marks << endl;
    }
}

void updateStudent() {
    int roll;
    cout << "Enter roll number of student to update: ";
    cin >> roll;

    for (int i = 0; i < studentCount; ++i) {
        if (students[i].rollNumber == roll) {
            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, students[i].name);
            cout << "Enter new marks: ";
            cin >> students[i].marks;
            cout << "Student updated successfully!" << endl;
            return;
        }
    }
    cout << "Student with roll number " << roll << " not found." << endl;
}

void deleteStudent() {
    int roll;
    cout << "Enter roll number of student to delete: ";
    cin >> roll;

    for (int i = 0; i < studentCount; ++i) {
        if (students[i].rollNumber == roll) {
            for (int j = i; j < studentCount - 1; ++j) {
                students[j] = students[j + 1];
            }
            studentCount--;
            cout << "Student deleted successfully!" << endl;
            return;
        }
    }
    cout << "Student with roll number " << roll << " not found." << endl;
}

void saveToFile() {
    ofstream file("students.txt");
    for (int i = 0; i < studentCount; ++i) {
        file << students[i].name << "\n" << students[i].rollNumber << "\n" << students[i].marks << "\n";
    }
    file.close();
    cout << "Data saved to file successfully." << endl;
}

void loadFromFile() {
    ifstream file("students.txt");
    if (!file) {
        cout << "No saved data found." << endl;
        return;
    }

    studentCount = 0;
    while (!file.eof() && studentCount < MAX_STUDENTS) {
        getline(file, students[studentCount].name);
        file >> students[studentCount].rollNumber;
        file >> students[studentCount].marks;
        file.ignore(); 
        studentCount++;
    }
    file.close();
    cout << "Data loaded from file successfully." << endl;
}

int main() {
    int choice;

    loadFromFile();

    while (true) {
        cout << "\nStudent Management System" << endl;
        cout << "1. Add Student\n2. Display Students\n3. Update Student\n4. Delete Student\n5. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            updateStudent();
            break;
        case 4:
            deleteStudent();
            break;
        case 5:
            saveToFile();
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }
}
