//
// Created by saidn on 5/2/2025.
//

#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H
#include <iostream>
#include <vector>

#include "student.h"
#include "User.h"

using namespace std;

class Instructor : public User {
public:
    vector<Course> courses;

    Instructor(int id, string username, string password, vector<Course> c) : User(id, username, password) {
        courses = c;
    }

    void add_course(Course& course) {
        if (courses.size() >= 5) {
            cout << "Cannot add more than 5 courses." << endl;
            return;
        }
        courses.push_back(course);
        cout << " added to list of courses successfully." << endl;
    }

    void remove_course(Course& course) {
        for (int i = 0; i < courses.size(); i++) {
            if (courses[i].code == course.code) {
                courses.erase(courses.begin() + i); // Correct erase usage
                cout << " removed from list of courses successfully." << endl;
                break;
            }
        }
    }

    void set_grade(Course& course, Student s, double grade) {
        course.setGrade(s.id,grade);
    }

    double max_grade(const Course& course) {
        vector<int>grades=course.grades;
        int maximum = -1;
        for (int i = 0;i < grades.size();i++) {
            if (grades[i] > maximum) {
                maximum = grades[i];
            }
        }
        return maximum;
    }

    double min_grade(const Course& course) {
        vector<int>grades=course.grades;
        int minimum = 200;
        for (int i = 0;i < grades.size();i++) {
            if (grades[i] < minimum) {
                minimum = grades[i];
            }
        }
        return minimum;
    }

    double avg_grade(const Course& course) {
        vector<int>grades=course.grades;
        double total = 0;
        for (int i = 0;i < grades.size();i++) {
            total += grades[i];
        }
        return total / grades.size();
    }
};


#endif //INSTRUCTOR_H
