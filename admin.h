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
private:
    vector<Course> course_list;
public:
    Administrator(int id, string username, string password) : User(id, username, password) {}

    void add_user(int id, string username, string password, string role, vector<Student>& student_list, vector<Instructor>& instructor_list) {
        for (const auto& instructor : instructor_list) {
            if (instructor.id == id || instructor.username == username) {
                cout << "User with same ID or username already exists" << endl;
                return;
            }
        }
        for (const auto& student : student_list) {
            if (student.id == id || student.username == username) {
                cout << "User with same ID or username already exists" << endl;
                return;
            }
        }

        if (role == "instructor") {
            vector<Course> courses;
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
            auto it = find_if(instructor_list.begin(), instructor_list.end(),
                            [id](const Instructor& instr) { return instr.id == id; });
            if (it != instructor_list.end()) {
                instructor_list.erase(it);
                cout << "Instructor removed successfully" << endl;
            } else {
                cout << "Instructor not found" << endl;
            }
        }
        else if (role == "student") {
            auto it = find_if(student_list.begin(), student_list.end(),
                            [id](const Student& stud) { return stud.id == id; });
            if (it != student_list.end()) {
                student_list.erase(it);
                cout << "Student removed successfully" << endl;
            } else {
                cout << "Student not found" << endl;
            }
        }
        else {
            cout << "Invalid role" << endl;
        }
    }


    void add_course(string name, int code, int credits, const vector<int>& grades,
                   const vector<int>& student_ids, const vector<int>& instructors_ids) {
        // Check for duplicate course code
        auto it = find_if(course_list.begin(), course_list.end(),
                         [code](const Course& course) { return course.code == code; });
        if (it != course_list.end()) {
            cout << "Course with same code already exists" << endl;
            return;
        }

        Course new_course(name, code, credits, grades, student_ids, instructors_ids);
        course_list.push_back(new_course);

        // Update instructor course lists
        for (auto& instructor : instructors_ids) {
            // You would need a way to find the instructor by ID and add the course to their list
            // This would require passing the instructor_list as a parameter or storing it in the Admin class
        }

        cout << "Course added successfully" << endl;
    }

    void remove_course(int code) {
        auto it = find_if(course_list.begin(), course_list.end(),
                         [code](const Course& course) { return course.code == code; });
        if (it != course_list.end()) {
            course_list.erase(it);
            cout << "Course removed successfully" << endl;
        } else {
            cout << "Course not found" << endl;
        }
    }

    // Getter for course_list
    const vector<Course>& get_course_list() const {
        return course_list;
    }
};

#endif //ADMIN_H