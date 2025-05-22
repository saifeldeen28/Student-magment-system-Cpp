//
// Created by saidn on 5/2/2025.
//

#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H
#include <iostream>


#include "student.h"
#include "User.h"

using namespace std;

class Instructor : public User {
private:
    Course* courses;
    int course_count;

public:
    // Setters
    void set_courses(Course* newCourses) { courses = newCourses; }

    // Getters
    Course* get_courses() const { return courses; }
    int get_courses_count() const { return course_count; }

    // Default Constructor
    Instructor() {
        set_user_type("instructor");
    }

    // Parameterized Constructor
    Instructor(int id, string username, string password, Course* c,int count) : User(id, username, password) {
        courses = c;
        course_count = count;
        set_user_type("instructor");
    }

    // Function to add a course
    void add_course(Course& course) {
        if (course_count >= 5) {
            cout << "Cannot add more than 5 courses." << endl;
            return;
        }
        for (int i = 0; i < course_count; i++) {
            if (courses[i].get_code() == course.get_code()) {
                cout << "Course already exists." << endl;
                return;
            }
        }
        course.add_instructor(get_id());
        Course* new_courses = new Course[course_count + 1];

        for (int i = 0; i < course_count; i++) {
            new_courses[i] = courses[i];
        }
        new_courses[course_count] = course;
        courses = new_courses;
        course_count++;
        cout << " added to list of courses successfully." << endl;
    }

    // Function to remove a course
    void remove_course(Course& course) {
        for (int i = 0; i < course_count; i++) {
            if (courses[i].get_code() == course.get_code()) {
                Course* new_courses = new Course[course_count - 1];  // Step 1: Allocate smaller array

                for (int j = 0; j < i; j++)                          // Step 2: Copy elements before `i`
                    new_courses[j] = courses[j];

                for (int j = i + 1; j < course_count; j++)           // Step 3: Copy elements after `i`
                    new_courses[j - 1] = courses[j];

                courses = new_courses;                    // Step 5: Update pointer
                course_count--;                                      // Step 6: Update count

                cout << " removed from list of courses successfully." << endl;
                break;
            }
        }
    }

    // Function to set or change a grade of a student
    void set_grade(Course& course, Student &s, int grade) {
        course.set_grade(s.get_id(),grade);
    }

    // Function to get the max grade in the course
    double max_grade(const Course& course) {
        int* grades=course.get_grades();
        int maximum = -1;
        for (int i = 0;i < course.get_number_of_students();i++) {
            if (grades[i] > maximum) {
                maximum = grades[i];
            }
        }
        return maximum;
    }

    // Function to get the min grade in the course
    double min_grade(const Course& course) {
        int* grades=course.get_grades();
        int minimum = 200;
        for (int i = 0;i < course.get_number_of_students() ;i++) {
            if (grades[i] < minimum) {
                minimum = grades[i];
            }
        }
        return minimum;
    }

    // Function to get the avgerage grade in the course
    double avg_grade(Course& course) {
        int* grades=course.get_grades();
        double total = 0;
        for (int i = 0;i < course.get_number_of_students();i++) {
            total += grades[i];
        }
        return total / course.get_number_of_students();
    }
    // Function to save the instructor data to a file
    void save() {

        ofstream file("itest.txt", ios::app);

        if (!file.is_open()) {
            cout << "Failed to open file" << endl;
            return;
        }

        file << get_id() << " " << get_username() << " " << get_password() << " " << get_courses_count() << " ";

        for (int i = 0; i < course_count; ++i) {
            file << courses[i].get_code() << " ";
        }

        file.close();
        cout << "Instructor data saved successfully.";
    }
};


#endif //INSTRUCTOR_H
