//
// Created by saidn on 5/2/2025.
//

#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H
#include <iostream>
#include <fstream>
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
    Instructor(int id, string username, string password, Course* c, int count) : User(id, username, password) {
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

                courses = new_courses;                               // Step 4: Update pointer
                course_count--;                                      // Step 5: Update count

                cout << " removed from list of courses successfully." << endl;
                break;
            }
        }
    }

    // Function to set or change a grade of a student
    void set_grade(Course& course, Student &s, int grade) {
        course.set_grade(s.get_id(), grade);
    }

    // Function to get the max grade in the course
    double max_grade(const Course& course) {
        int* grades = course.get_grades();
        int maximum = -1;
        for (int i = 0; i < course.get_number_of_students(); i++) {
            if (grades[i] > maximum) {
                maximum = grades[i];
            }
        }
        return maximum;
    }

    // Function to get the min grade in the course
    double min_grade(const Course& course) {
        int* grades = course.get_grades();
        int minimum = 200;
        for (int i = 0; i < course.get_number_of_students(); i++) {
            if (grades[i] < minimum) {
                minimum = grades[i];
            }
        }
        return minimum;
    }

    // Function to get the average grade in the course
    double avg_grade(Course& course) {
        int* grades = course.get_grades();
        double total = 0;
        for (int i = 0; i < course.get_number_of_students(); i++) {
            total += grades[i];
        }
        return total / course.get_number_of_students();
    }

    // Function to save the instructor data to a file
    void save() {
        ofstream file("instructors.txt", ios::app);

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
    
    // Function to display instructor performance report
    void performance_I() {
        cout << "========================================" << endl;
        cout << "         Instructor Performance          " << endl;
        cout << "========================================" << endl;
        cout << "Instructor: " << get_username() << endl;
        cout << "Courses Taught: " << course_count << endl;
        cout << "========================================" << endl;

        if (course_count == 0) {
            cout << "No courses assigned to this instructor" << endl;
            return;
        }

        for (int i = 0; i < course_count; i++) {
            Course &c = courses[i];
            cout << "Course: " << c.get_name() << endl;
            cout << "----------------------------------------" << endl;
            cout << "Students: " << c.get_number_of_students() << endl;
            cout << "Average Grade: " << avg_grade(c) << endl;
            cout << "Max Grade: " << max_grade(c) << endl;
            cout << "Min Grade: " << min_grade(c) << endl;
            cout << "Passing Students: " << c.get_passing_students() << endl;
            cout << "Failing Students: " << c.get_failing_students() << endl;

            int a = 0, b = 0, _c = 0, d = 0, f = 0;
            int *grades = c.get_grades();
            int n = c.get_number_of_students();
            for (int j = 0; j < n; j++) {
                int g = grades[j];
                if (g >= 90) a++;
                else if (g >= 80) b++;
                else if (g >= 70) _c++;
                else if (g >= 50) d++;
                else f++;
            }

            cout << "Grade Distribution:" << endl;
            cout << "  A: " << a << endl;
            cout << "  B: " << b << endl;
            cout << "  C: " << _c << endl;
            cout << "  D: " << d << endl;
            cout << "  F: " << f << endl;

            cout << "----------------------------------------" << endl;
        }

        cout << "========================================" << endl;
    }
};

#endif //INSTRUCTOR_H
