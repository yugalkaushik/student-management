#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

// Structure to hold student information
struct Student {
    string name;
    string regNumber;
    int age;
    char gender;
    string course;
};

// Function prototypes
void readStudents(vector<Student>& students);
void displayStudents(const vector<Student>& students);
void addStudent(vector<Student>& students, vector<string>& courses);
void saveStudents(const vector<Student>& students);

void readCourses(vector<string>& courses);
void displayCourses(const vector<string>& courses);
void addCourse(vector<string>& courses);
void saveCourses(const vector<string>& courses);
void addSubjectsToCourse(vector<string>& courses);

int main() {
    vector<Student> students;
    vector<string> courses;

    // Read initial data from files
    readStudents(students);
    readCourses(courses);

    int choice;
    do {
        cout << "\n===== Student Management System Menu =====\n";
        cout << "1. Display all students\n";
        cout << "2. Add a student\n";
        cout << "3. Display all courses\n";
        cout << "4. Add a course\n";
        cout << "5. Add subjects to a course\n";
        cout << "6. Save and exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline left in the input buffer

        switch(choice) {
            case 1:
                displayStudents(students);
                break;
            case 2:
                addStudent(students, courses);
                break;
            case 3:
                displayCourses(courses);
                break;
            case 4:
                addCourse(courses);
                break;
            case 5:
                addSubjectsToCourse(courses);
                break;
            case 6:
                saveStudents(students);
                saveCourses(courses);
                cout << "Data saved. Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6.\n";
        }
    } while(choice != 6);

    return 0;
}

void readStudents(vector<Student>& students) {
    ifstream file("students.txt");
    if (!file) {
        cout << "Error opening students.txt. Exiting...\n";
        exit(1);
    }

    students.clear();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        Student student;
        ss >> student.name >> student.regNumber >> student.age >> student.gender >> student.course;
        students.push_back(student);
    }
    file.close();
}

void displayStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students registered.\n";
        return;
    }

    cout << "\n===== List of Students =====\n";
    for (const auto& student : students) {
        cout << "Name: " << student.name << ", Reg. Number: " << student.regNumber
             << ", Age: " << student.age << ", Gender: " << student.gender
             << ", Course: " << student.course << endl;
    }
}

void addStudent(vector<Student>& students, vector<string>& courses) {
    Student newStudent;
    cout << "\nEnter student details:\n";
    cout << "Name: ";
    getline(cin, newStudent.name);

    cout << "Registration Number: ";
    getline(cin, newStudent.regNumber);

    cout << "Age: ";
    cin >> newStudent.age;
    cin.ignore(); // Ignore newline left in the input buffer

    cout << "Gender (M/F): ";
    cin >> newStudent.gender;
    cin.ignore(); // Ignore newline left in the input buffer

    // Display courses and allow the user to select or add a new course
    displayCourses(courses);
    if (!courses.empty()) {
        int choice;
        cout << "Select a course number (or enter 0 to add a new course): ";
        cin >> choice;
        cin.ignore(); // Ignore newline left in the input buffer

        if (choice >= 1 && choice <= courses.size()) {
            newStudent.course = courses[choice - 1];
        } else if (choice == 0) {
            addCourse(courses);
            newStudent.course = courses.back(); // Use the newly added course
        } else {
            cout << "Invalid choice. Using default course.\n";
            newStudent.course = "Unknown";
        }
    } else {
        cout << "No courses available. Adding student with default course.\n";
        newStudent.course = "Unknown";
    }

    students.push_back(newStudent);
    cout << "Student added successfully.\n";

    // Save the updated list of students to file
    saveStudents(students);
}

void saveStudents(const vector<Student>& students) {
    ofstream file("students.txt");
    if (!file) {
        cout << "Error saving students to file.\n";
        return;
    }

    for (const auto& student : students) {
        file << student.name << " " << student.regNumber << " " << student.age << " "
             << student.gender << " " << student.course << "\n";
    }
    file.close();
}

void readCourses(vector<string>& courses) {
    ifstream file("courses.txt");
    if (!file) {
        cout << "Error opening courses.txt. Exiting...\n";
        exit(1);
    }

    courses.clear();
    string course;
    while (getline(file, course)) {
        courses.push_back(course);
    }
    file.close();
}

void displayCourses(const vector<string>& courses) {
    if (courses.empty()) {
        cout << "No courses available.\n";
        return;
    }

    cout << "\n===== List of Courses =====\n";
    for (size_t i = 0; i < courses.size(); ++i) {
        cout << i + 1 << ". " << courses[i] << endl;
    }
}

void addCourse(vector<string>& courses) {
    string newCourse;
    cout << "\nEnter course name to add: ";
    getline(cin, newCourse);
    courses.push_back(newCourse);
    cout << "Course added successfully.\n";

    // Save the updated list of courses to file
    saveCourses(courses);
}

void saveCourses(const vector<string>& courses) {
    ofstream file("courses.txt");
    if (!file) {
        cout << "Error saving courses to file.\n";
        return;
    }

    for (const auto& course : courses) {
        file << course << "\n";
    }
    file.close();
}

void addSubjectsToCourse(vector<string>& courses) {
    displayCourses(courses);
    if (courses.empty()) {
        cout << "No courses available to add subjects to.\n";
        return;
    }

    int courseIndex;
    cout << "\nEnter the index of the course to add subjects: ";
    cin >> courseIndex;
    cin.ignore(); // Ignore newline left in the input buffer

    if (courseIndex < 1 || courseIndex > courses.size()) {
        cout << "Invalid course index.\n";
        return;
    }

    string subjects;
    cout << "Enter subjects to add to " << courses[courseIndex - 1] << " (separate by commas): ";
    getline(cin, subjects);

    // Append subjects to the selected course
    courses[courseIndex - 1] += ": " + subjects;
    cout << "Subjects added to course " << courses[courseIndex - 1] << " successfully.\n";

    // Save the updated list of courses to file
    saveCourses(courses);
}
