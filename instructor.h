//
// Created by saidn on 5/2/2025.
//

#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H
#include <iostream>
#include <vector>
#include "User.h"

using namespace std;

class Instructor : public User {
public:
    vector<Course> courses;

    Instructor(int id, string username, string password, vector<Course> c) : User(id, username, password) {
        courses = c;
    }

    void add_course(course& course) {
        if (courses.size() >= 5) {
            cout << "Cannot add more than 5 courses." << endl;
            return;
        }
        courses.push_back(course);
        cout << " added to list of courses successfully." << endl;
    }

    void remove_course(course& course) {
        for (auto it = courses.begin();it != courses.end();it++) {
            if (course == *it) {
                courses.erase(it);
                cout << " removed from list of courses successfully." << endl;
                break;
            }
        }

    }

    void set_grade(Course& course, Student s, double grade) {
        //verify ya 5wl student has the course; 
        course.setGrade(s.id,grade);
    }

    double max_grade(const Course& course) {
        vector<int>grades=course.grades;
        maximum = -1;
        for (int i = 0;i < grades.size();i++) {
            if (grades[i] > maximum) {
                maximum = grades[i];
            }
        }
        return maximum;
    }

    double min_grade(const Course& course) {
        vector<int>grades=course.grades;
        minimum = 200;
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
