#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Student {
private:
    int rollNo;
    string name;
    int age;
    string course;
    float marks;

public:
    Student() {}

    Student(int r, string n, int a, string c, float m) {
        rollNo = r;
        name = n;
        age = a;
        course = c;
        marks = m;
    }

    int getRollNo() {
        return rollNo;
    }

    void inputStudent() {
        cout << "Enter Roll Number: ";
        cin >> rollNo;

        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cin.ignore();

        cout << "Enter Course: ";
        getline(cin, course);

        cout << "Enter Marks: ";
        cin >> marks;
    }

    void displayStudent() {
        cout << "Roll No: " << rollNo << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Course: " << course << endl;
        cout << "Marks: " << marks << endl;
        cout << "------------------------" << endl;
    }

    void saveToFile(ofstream &file) {
        file << rollNo << endl;
        file << name << endl;
        file << age << endl;
        file << course << endl;
        file << marks << endl;
    }

    void readFromFile(ifstream &file) {
        file >> rollNo;
        file.ignore();

        getline(file, name);

        file >> age;
        file.ignore();

        getline(file, course);

        file >> marks;
        file.ignore();
    }
};

class StudentManager {
private:
    vector<Student> students;
    string filename = "students.txt";

public:
    StudentManager() {
        loadFromFile();
    }

    void loadFromFile() {
        students.clear();

        ifstream file(filename);

        if (!file) {
            return;
        }

        while (file.peek() != EOF) {
            Student s;
            s.readFromFile(file);

            if (file) {
                students.push_back(s);
            }
        }

        file.close();
    }

    void saveAllToFile() {
        ofstream file(filename);

        for (Student s : students) {
            s.saveToFile(file);
        }

        file.close();
    }

    bool isRollNoExists(int rollNo) {
        for (Student s : students) {
            if (s.getRollNo() == rollNo) {
                return true;
            }
        }
        return false;
    }

    void addStudent() {
        Student s;
        s.inputStudent();

        if (isRollNoExists(s.getRollNo())) {
            cout << "Student with this Roll Number already exists!" << endl;
            return;
        }

        students.push_back(s);
        saveAllToFile();

        cout << "Student added successfully!" << endl;
    }

    void displayAllStudents() {
        if (students.empty()) {
            cout << "No student records found." << endl;
            return;
        }

        for (Student s : students) {
            s.displayStudent();
        }
    }

    void searchStudent() {
        int rollNo;
        cout << "Enter Roll Number to search: ";
        cin >> rollNo;

        for (Student s : students) {
            if (s.getRollNo() == rollNo) {
                cout << "Student Found:" << endl;
                s.displayStudent();
                return;
            }
        }

        cout << "Student not found." << endl;
    }

    void updateStudent() {
        int rollNo;
        cout << "Enter Roll Number to update: ";
        cin >> rollNo;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].getRollNo() == rollNo) {
                cout << "Enter new details:" << endl;

                Student updatedStudent;
                updatedStudent.inputStudent();

                students[i] = updatedStudent;
                saveAllToFile();

                cout << "Student updated successfully!" << endl;
                return;
            }
        }

        cout << "Student not found." << endl;
    }

    void deleteStudent() {
        int rollNo;
        cout << "Enter Roll Number to delete: ";
        cin >> rollNo;

        for (int i = 0; i < students.size(); i++) {
            if (students[i].getRollNo() == rollNo) {
                students.erase(students.begin() + i);
                saveAllToFile();

                cout << "Student deleted successfully!" << endl;
                return;
            }
        }

        cout << "Student not found." << endl;
    }
};

int main() {
    StudentManager manager;

    int choice;

    do {
        cout << "\n===== Student Management System =====" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display All Students" << endl;
        cout << "3. Search Student" << endl;
        cout << "4. Update Student" << endl;
        cout << "5. Delete Student" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.addStudent();
                break;

            case 2:
                manager.displayAllStudents();
                break;

            case 3:
                manager.searchStudent();
                break;

            case 4:
                manager.updateStudent();
                break;

            case 5:
                manager.deleteStudent();
                break;

            case 6:
                cout << "Exiting program..." << endl;
                break;

            default:
                cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 6);

    return 0;
}