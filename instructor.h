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

    Course* courses;
    int course_count;

public:
    void setCourses(Course* newCourses) { courses = newCourses; }
    Course* getCourses() const { return courses; }

    Instructor() {
        setUserType("instructor");
    }
    Instructor(int id, string username, string password, Course* c,int count) : User(id, username, password) {
        courses = c;
        course_count = count;
        setUserType("instructor");
    }

    void add_course(Course& course) {
        if (course_count >= 5) {
            cout << "Cannot add more than 5 courses." << endl;
            return;
        }
        Course* new_courses = new Course[course_count + 1];

        for (int i = 0; i < course_count; i++)
            new_courses[i] = courses[i];

        new_courses[course_count] = course;

        delete[] courses;

        courses = new_courses;
        course_count++;

        cout << " added to list of courses successfully." << endl;
    }

    void remove_course(Course& course) {
        for (int i = 0; i < course_count; i++) {
            if (courses[i].getCode() == course.getCode()) {
                Course* new_courses = new Course[course_count - 1];  // Step 1: Allocate smaller array

                for (int j = 0; j < i; j++)                          // Step 2: Copy elements before `i`
                    new_courses[j] = courses[j];

                for (int j = i + 1; j < course_count; j++)           // Step 3: Copy elements after `i`
                    new_courses[j - 1] = courses[j];

                delete[] courses;                         // Step 4: Delete old array
                courses = new_courses;                    // Step 5: Update pointer
                course_count--;                                      // Step 6: Update count

                cout << " removed from list of courses successfully." << endl;
                break;
            }
        }
    }

    void set_grade(Course& course, Student &s, int grade) {
        course.setGrade(s.getId(),grade);
    }

    double max_grade(const Course& course) {
        int* grades=course.getGrades();
        int maximum = -1;
        for (int i = 0;i < course.get_number_of_students();i++) {
            if (grades[i] > maximum) {
                maximum = grades[i];
            }
        }
        return maximum;
    }

    double min_grade(const Course& course) {
        int* grades=course.getGrades();
        int minimum = 200;
        for (int i = 0;i < course.get_number_of_students() ;i++) {
            if (grades[i] < minimum) {
                minimum = grades[i];
            }
        }
        return minimum;
    }

    double avg_grade(Course& course) {
        int* grades=course.getGrades();
        double total = 0;
        for (int i = 0;i < course.get_number_of_students();i++) {
            total += grades[i];
        }
        return total / course.get_number_of_students();
    }



    // Copy assignment operator
    Instructor& operator=(const Instructor& other) {
        // Self-assignment check
        if (this == &other) {
            return *this;
        }

        // Call base class assignment operator to handle User members
        User::operator=(other);

        // Copy primitive types
        course_count = other.course_count;

        // Delete existing courses array
        delete[] courses;

        // Allocate new memory for courses
        courses = new Course[course_count];

        // Deep copy each Course object
        for (int i = 0; i < course_count; i++) {
            courses[i] = other.courses[i];  // This uses Course's copy assignment operator
        }

        // Return reference to current object
        return *this;
    }
};


#endif //INSTRUCTOR_H
