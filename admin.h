//
// Created by saidn on 5/1/2025.
//

#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <map>
#include <vector>
#include "User.h"


using namespace std;
class Instructor : public User {
public:
    Instructor(int id, string username, string password) : User(id, username, password) {}
};

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

        for (int i = 0; i < student_list.size(); i++) {
            if (student_list[i].id == id || student_list[i].username == username) {
                cout << "User with same ID or username already exists" << endl;
                return;
            }
        }
        if (role == "instructor") {
            Instructor new_instructor(id, username, password);
            instructor_list.push_back(new_instructor);
            cout << "Instructor added successfully" << endl;
        }
        else if (role == "student") {
            Student new_student;
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
            for (size_t i = 0; i < instructor_list.size(); i++) {
                if (instructor_list[i].id == id) {
                    instructor_list.erase(instructor_list.begin() + i);
                    cout << "Instructor removed successfully" << endl;
                    return;
                }
            }
            cout << "Instructor not found" << endl;
        }
        else if (role == "student") {
            for (size_t i = 0; i < student_list.size(); i++) {
                if (student_list[i].id == id) {
                    student_list.erase(student_list.begin() + i);
                    cout << "Student removed successfully" << endl;
                    return;
                }
            }
            cout << "Student not found" << endl;
        }
        else {
            cout << "Invalid role" << endl;
        }
    }

    void add_course(vector<Course>& course_list, string name, int code, vector<int> instructors_ids, int credits, vector<int> grades) {
        Course new_course(name, code, credits, grades);
        new_course.instructors_ids = instructors_ids;
        course_list.push_back(new_course);
        cout << "Course added successfully" << endl;
    }

    void remove_course(vector<Course>& course_list, int code) {
        for (size_t i = 0; i < course_list.size(); i++) {
            if (course_list[i].code == code) {
                course_list.erase(course_list.begin() + i);
                cout << "Course removed successfully" << endl;
                return;
            }
        }
        cout << "Course not found" << endl;
    }
};


#endif //ADMIN_H
