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
    Student() {
        set_user_type("student");
    }
    Student(int id, string username, string password) : User(id, username, password) {
        course_count = 0;
        set_user_type("student");
    }

    bool add(Course &course, int grade=0) {
        if (course_count >= MAX_COURSES) {
            cout << "You have reached the maximum number of courses" << endl;
            return false;
        }

        if (!course.add_student(get_id(), grade)) {
            cout << "Couldn't add student" << endl;
            return false;
        }

        registered_courses[course_count] = &course;
        course_count++;

        cout << "Successfully registered for course: " << course.get_name() << endl;
        return true;
    }


    bool drop(Course& course)
    {
        if (course.drop_student(get_id())) {
            cout << "Course dropped successfully" << endl;
            return true;
        }
        cout << "Couldn't drop student" << endl;
        return false;
    }

    void view_grades() {
        if (course_count == 0) {
            cout << "You are not registered in any courses" << endl;
            return;
        }

        cout << "Your Grades:" << endl;
        for (int i = 0; i < course_count; i++) {
            cout << "Course: " << registered_courses[i]->get_name()
                 << " | Grade: " << registered_courses[i]->get_grade(get_id()) << endl;
        }
    }

    void average_grade() {
        if (course_count == 0) {
            cout << "No grades available to calculate average" << endl;
            return;
        }

        double sum = 0;
        for (int i = 0; i < course_count; i++) {
            sum += registered_courses[i]->get_grade(get_id());
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

    double calculate_GPA()
    {
        if (course_count == 0) {
            cout << "No registered courses. GPA is 0.0" << endl;
            return 0.0;
        }

        double total = 0.0;
        int total_credits = 0;

        for (int i = 0; i < course_count; ++i) {
            int grade = registered_courses[i]->get_grade(get_id());
            int credits = registered_courses[i]->get_credits();

            total += grade * credits;
            total_credits += credits;
        }

        double GPA = (total_credits > 0) ? total / total_credits : 0.0;
        cout << "GPA: " << GPA << endl;
        return GPA;
    }
};

#endif // STUDENT_H
