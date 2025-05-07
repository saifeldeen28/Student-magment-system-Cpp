#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include "Course.h"
#include "User.h"
using namespace std;

class Student : public User {

    const int MAX_COURSES = 6;
    Course* registered_courses[6]; // now stores pointers
    int course_count;

public:
    Student():User(){}
    Student(int id, string username, string password) : User(id, username, password) {
        course_count = 0;
    }

    bool add(Course &course, int grade=0) {
        if (course_count >= MAX_COURSES) {
            cout << "You have reached the maximum number of courses" << endl;
            return false;
        }

        if (!course.add_student(getId(), grade)) {
            cout << "Couldn't add student" << endl;
            return false;
        }

        registered_courses[course_count] = &course;
        course_count++;

        cout << "Successfully registered for course: " << course.getName() << endl;
        return true;
    }


    bool drop(Course& course)
    {
        if (course.drop_stuent(getId())) {
            cout << "Course dropped successfully" << endl;
            return true;
        }
        cout << "Couldn't drop student" << endl;
        return false;
    }

    void viewGrades() {
        if (course_count == 0) {
            cout << "You are not registered in any courses" << endl;
            return;
        }

        cout << "Your Grades:" << endl;
        for (int i = 0; i < course_count; i++) {
            cout << "Course: " << registered_courses[i]->getName()
                 << " | Grade: " << registered_courses[i]->getGrade(getId()) << endl;
        }
    }

    void averageGrade() {
        if (course_count == 0) {
            cout << "No grades available to calculate average" << endl;
            return;
        }

        double sum = 0;
        for (int i = 0; i < course_count; i++) {
            sum += registered_courses[i]->getGrade(getId());
        }

        cout << "Average Grade: " << sum / course_count << endl;
    }



    int get_Number_Of_Courses()
    {
        return course_count ;
    }





    // Copy assignment operator
    Student& operator=(const Student& other) {
        // Self-assignment check
        if (this == &other) {
            return *this;
        }

        // Call base class assignment operator to handle User members
        User::operator=(other);

        // Copy primitive types
        course_count = other.course_count;

        // Copy the array of Course pointers
        // Note: We're copying pointers, not deep copying the courses themselves
        // This is consistent with the add() method that stores references to existing courses
        for (int i = 0; i < course_count; i++) {
            registered_courses[i] = other.registered_courses[i];
        }

        // Return reference to current object
        return *this;
    }
};

#endif // STUDENT_H
