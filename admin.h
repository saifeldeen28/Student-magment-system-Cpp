#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include "User.h"
#include "Course.h"
#include "student.h"
#include "instructor.h"

using namespace std;

class Administrator : public User {
    Course* course_list;
    int course_count;

public:
    Administrator(int id, string username, string password,Course* l=nullptr,int count=0)
        : User(id, username, password){
        course_count = count;
        course_list = l;
    }


    void add_student(int id, string username, string password, Student* student_list,
                    int& student_count) {
        // Check if student with same ID or username exists
        for (int i = 0; i < student_count; i++) {
            if (student_list[i].getId() == id || student_list[i].getUsername() == username) {
                cout << "Student with same ID or username already exists" << endl;
                return;
            }
        }

        Student new_student(id, username, password);
        Student* new_student_list=new Student[student_count+1];
        for (int i = 0; i < student_count; i++) {
            new_student_list[i]=student_list[i];
        }

        cout << "Student added successfully" << endl;
    }
	void setCourseList(Course* list) {
          course_list = list;
	}
    void add_instructor(int id, string username, string password, Instructor* instructor_list,
                       int& instructor_count) {
        // Check if instructor with same ID or username exists
        for (int i = 0; i < instructor_count; i++) {
            if (instructor_list[i].getId() == id || instructor_list[i].getUsername() == username) {
                cout << "Instructor with same ID or username already exists" << endl;
                return;
            }
        }


        Course* courses = nullptr;
        Instructor new_instructor(id, username, password, courses, 0);
        instructor_list[instructor_count++] = new_instructor;
        cout << "Instructor added successfully" << endl;
    }

    void remove_student(Student* student_list, int& student_count, int id) {
        bool found = false;
        for (int i = 0; i < student_count; i++) {
            if (student_list[i].getId() == id) {
                // Shift remaining elements left
                for (int j = i; j < student_count - 1; j++) {
                    student_list[j] = student_list[j + 1];
                }
                student_count--;
                cout << "Student removed successfully" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student not found" << endl;
        }
    }

    void remove_instructor(Instructor* instructor_list, int& instructor_count, int id) {
        bool found = false;
        for (int i = 0; i < instructor_count; i++) {
            if (instructor_list[i].getId() == id) {
                for (int j = i; j < instructor_count - 1; j++) {
                    instructor_list[j] = instructor_list[j + 1];
                }
                instructor_count--;
                cout << "Instructor removed successfully" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Instructor not found" << endl;
        }
    }

    void add_course(string name, int code, int credits, int* grades,
                   int* student_ids, int* instructors_ids, int num_students, int num_instructors) {

        for (int i = 0; i < course_count; i++) {
            if (course_list[i].getCode() == code) {
                cout << "Course with same code already exists" << endl;
                return;
            }
        }

        Course new_course(name, code, credits, student_ids, grades, num_students, instructors_ids, num_instructors);
        course_list[course_count++] = new_course;
        cout << "Course added successfully" << endl;
    }

    void remove_course(int code) {
        bool found = false;
        for (int i = 0; i < course_count; i++) {
            if (course_list[i].getCode() == code) {
                // Shift remaining elements left
                for (int j = i; j < course_count - 1; j++) {
                    course_list[j] = course_list[j + 1];
                }
                course_count--;
                cout << "Course removed successfully" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Course not found" << endl;
        }
    }

    const Course* get_course_list() const {
        return course_list;
    }

    int get_course_count() const {
        return course_count;
    }
    void show_main_menu(Student* student_list, int& student_count, Instructor* instructor_list, int& instructor_count) {
        int choice = 0;
        while (choice != 5) {
            cout << "\n=== Administrator Menu ===\n";
            cout << "1. Add a new user (student/instructor)\n";
            cout << "2. Remove a user\n";
            cout << "3. Add a new course\n";
            cout << "4. Remove a course\n";
            cout << "5. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    int user_type;
                    cout << "\n=== Add User ===\n";
                    cout << "1. Add Student\n";
                    cout << "2. Add Instructor\n";
                    cout << "Enter choice: ";
                    cin >> user_type;

                    int id;
                    string username, password;

                    cout << "Enter user ID: ";
                    cin >> id;
                    cout << "Enter username: ";
                    cin >> username;
                    cout << "Enter password: ";
                    cin >> password;

                    if (user_type == 1) {
                        add_student(id, username, password, student_list, student_count);
                    } else if (user_type == 2) {
                        add_instructor(id, username, password, instructor_list, instructor_count);
                    } else {
                        cout << "Invalid choice\n";
                    }
                    break;
                }
                case 2: {
                    int user_type;
                    cout << "\n=== Remove User ===\n";
                    cout << "1. Remove Student\n";
                    cout << "2. Remove Instructor\n";
                    cout << "Enter choice: ";
                    cin >> user_type;

                    int id;
                    cout << "Enter user ID to remove: ";
                    cin >> id;

                    if (user_type == 1) {
                        remove_student(student_list, student_count, id);
                    } else if (user_type == 2) {
                        remove_instructor(instructor_list, instructor_count, id);
                    } else {
                        cout << "Invalid choice\n";
                    }
                    break;
                }
                case 3: {
                    string name;
                    int code, credits, num_students = 0, num_instructors = 0;

                    cout << "\n=== Add Course ===\n";
                    cout << "Enter course name: ";
                    cin >> name;
                    cout << "Enter course code: ";
                    cin >> code;
                    cout << "Enter credits: ";
                    cin >> credits;

                    cout << "Enter number of students (0 for none): ";
                    cin >> num_students;

                    int* student_ids = new int[num_students];
                    int* grades = new int[num_students];

                    for (int i = 0; i < num_students; i++) {
                        cout << "Enter student ID " << (i+1) << ": ";
                        cin >> student_ids[i];
                        cout << "Enter grade for student " << student_ids[i] << ": ";
                        cin >> grades[i];
                    }

                    cout << "Enter number of instructors (0-3): ";
                    cin >> num_instructors;
                    if (num_instructors > 3) num_instructors = 3; // Maximum 3 instructors per course

                    int* instructor_ids = new int[num_instructors];
                    for (int i = 0; i < num_instructors; i++) {
                        cout << "Enter instructor ID " << (i+1) << ": ";
                        cin >> instructor_ids[i];
                    }

                    add_course(name, code, credits, grades, student_ids, instructor_ids, num_students, num_instructors);

                    delete[] student_ids;
                    delete[] grades;
                    delete[] instructor_ids;
                    break;
                }
                case 4: {
                    int code;
                    cout << "\n=== Remove Course ===\n";
                    cout << "Enter course code to remove: ";
                    cin >> code;
                    remove_course(code);
                    break;
                }
                case 5:
                    cout << "Exiting administrator menu.\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        }
    }


};

#endif //ADMIN_H