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
    void set_courses(Course* newCourses);

    // Getters
    Course* get_courses() const;
    int get_courses_count() const;

    // Default Constructor
    Instructor();

    // Parameterized Constructor
    Instructor(int id, string username, string password, Course* c, int count);

    // Function to add a course
    void add_course(Course& course);

    // Function to remove a course
    void remove_course(Course& course);

    // Function to set or change a grade of a student
    void set_grade(Course& course, Student &s, int grade);

    // Function to get the max grade in the course
    double max_grade(const Course& course);

    // Function to get the min grade in the course
    double min_grade(const Course& course);

    // Function to get the average grade in the course
    double avg_grade(Course& course);
    
    // Function to save the instructor data to a file
    void save();
    
    // Function to display instructor performance report
    void performance_I();
};

#endif //INSTRUCTOR_H
