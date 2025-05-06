//
// Created by saidn on 5/1/2025.
//

#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <map>
#include <vector>
#include "User.h"
#include "Course.h"
#include "student.h"
#include "instructor.h"
using namespace std;

class Administrator : public User {
public:
    Administrator(int id, string username, string password) : User(id, username, password) {}

    void add_user(int id, string username, string password, string role, vector<Student>& student_list, vector<Instructor>& instructor_list) {
        for (int i = 0; i < instructor_list.size(); i++) {
            if (instructor_list[i].id == id || instructor_list[i].username == username) {
                cout << "User with same ID or username already exists" << endl;
                return;
            }
        }

        // Check students
        for (int i = 0; i < student_list.size(); i++) {
            if (student_list[i].id == id || student_list[i].username == username) {
                cout << "User with same ID or username already exists" << endl;
                return;
            }
        }

        if (role == "instructor") {
            Instructor new_instructor(id, username, password, courses);
            instructor_list.push_back(new_instructor);
            cout << "Instructor added successfully" << endl;
        }
        else if (role == "student") {
            Student new_student(id, username, password);
            student_list.push_back(new_student);
            cout << "Student added successfully" << endl;
        }
        else {
            cout << "Invalid role" << endl;
        }
    }

    void remove_user(vector<Instructor>& instructor_list, vector<Student>& student_list,
                    int id, string role) {
        if (role == "instructor") {
            bool found = false;
            for (int i = 0; i < instructor_list.size(); i++) {
                if (instructor_list[i].id == id) {
                    instructor_list.erase(instructor_list.begin() + i);
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
            for (int i = 0; i < student_list.size(); i++) {
                if (student_list[i].id == id) {
                    student_list.erase(student_list.begin() + i);
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

    void add_course(string name,const int code, int credits, const vector<int> &grades, const vector<int> &student_ids, const vector<int> &instructors_ids) {
        for (int i = 0; i < course_list.size(); i++) {
            if (course_list[i].code == code) {
                cout << "Course with same code already exists" << endl;
                return;
            }
        }

        Course new_course(name, code, credits, grades, student_ids, instructors_ids);
        new_course.instructors_ids = instructors_ids;
        course_list.push_back(new_course);
        cout << "Course added successfully" << endl;
    }

    void remove_course(vector<Course>& course_list, int code) {
        bool found = false;  // Added flag for better control
        for (int i = 0; i < course_list.size(); i++) {
            if (course_list[i].code == code) {
                course_list.erase(course_list.begin() + i);
                cout << "Course removed successfully" << endl;
                found = true;
                break;  // Exit loop after removal
            }
        }
        if (!found) {
            cout << "Course not found" << endl;
        }
    }
};

#endif //ADMIN_H