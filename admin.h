#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include "User.h"
#include "Course.h"
#include "student.h"
#include "instructor.h"

using namespace std;

class Administrator : public User {
    static const int MAX_COURSES = 100;
    Course course_list[MAX_COURSES];
    int course_count;

public:
    Administrator(int id, string username, string password) : User(id, username, password) {
        course_count = 0;
    }

    void add_user(int id, string username, string password, string role, Student* student_list, int& student_count,
                 Instructor* instructor_list, int& instructor_count, int max_students, int max_instructors) {
        for (int i = 0; i < instructor_count; i++) {
            if (instructor_list[i].getId() == id || instructor_list[i].getUsername() == username) {
                cout << "User with same ID or username already exists" << endl;
                return;
            }
        }

        for (int i = 0; i < student_count; i++) {
            if (student_list[i].getId() == id || student_list[i].getUsername() == username) {
                cout << "User with same ID or username already exists" << endl;
                return;
            }
        }

        if (role == "instructor") {
            if (instructor_count >= max_instructors) {
                cout << "Maximum number of instructors reached" << endl;
                return;
            }
            Course* courses = nullptr;
            Instructor new_instructor(id, username, password, courses, 0);
            instructor_list[instructor_count++] = new_instructor;
            cout << "Instructor added successfully" << endl;
        }
        else if (role == "student") {
            if (student_count >= max_students) {
                cout << "Maximum number of students reached" << endl;
                return;
            }
            Student new_student(id, username, password);
            student_list[student_count++] = new_student;
            cout << "Student added successfully" << endl;
        }
        else {
            cout << "Invalid role" << endl;
        }
    }

    void remove_user(Instructor* instructor_list, int& instructor_count,
                    Student* student_list, int& student_count,
                    int id, string role) {
        if (role == "instructor") {
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
        else if (role == "student") {
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
        else {
            cout << "Invalid role" << endl;
        }
    }

    void add_course(string name, int code, int credits, int* grades,
                   int* student_ids, int* instructors_ids, int num_students, int num_instructors) {
        if (course_count >= MAX_COURSES) {
            cout << "Maximum number of courses reached" << endl;
            return;
        }
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
};

#endif //ADMIN_H