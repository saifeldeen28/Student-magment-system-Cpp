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

    Course* courses;
    int course_count;

public:
    void set_courses(Course* newCourses);
    Course* get_courses() const;
    int get_courses_count() const;

    Instructor();
    Instructor(int id, string username, string password, Course* c, int count);

    void add_course(Course& course);

    void remove_course(Course& course);

    void set_grade(Course& course, Student &s, int grade);

    double max_grade(const Course& course);

    double min_grade(const Course& course);

    double avg_grade(Course& course);
};


#endif //INSTRUCTOR_H
