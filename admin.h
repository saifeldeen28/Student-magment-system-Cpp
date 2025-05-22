#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include "User.h"
#include "Course.h"
#include "student.h"
#include "instructor.h"

using namespace std;

class Administrator : public User {
    Course course_list[20];
    int course_count;

public:
    Administrator(int id, string username, string password, Course l[20]=nullptr, int count = 0);

    void view_students(const Student* student_list, int student_count);
    void view_instructors(const Instructor* instructor_list, int instructor_count);
    void add_student(int id, string username, string password, Student* student_list, int& student_count);
    void set_course_list(Course* list);
    void add_instructor(int id, string username, string password, Instructor* instructor_list, int& instructor_count);
    void remove_student(Student* student_list, int& student_count, int id);
    void remove_instructor(Instructor* instructor_list, int& instructor_count, int id);
    void add_course(const string &name, int code, int credits, int* instructors_ids, int num_instructors,
                   Instructor* instructor_list, int instructor_count);
    void remove_course(int code);
    const Course* get_course_list() const;
    int get_course_count() const;
};

#endif //ADMIN_H