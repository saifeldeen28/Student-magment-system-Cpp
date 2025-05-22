#include <iostream>
#include <fstream>
#include "Course.h"
#include "User.h"

using namespace std;

class Student : public User {
private:
    static const int MAX_COURSES = 6;
    Course* registered_courses[MAX_COURSES];
    int course_count;

public:
    Student();
    Student(int id, string username, string password);

    bool add(Course& course, int grade = 0);
    bool drop(Course& course);
    void view_grades();
    void average_grade();
    double calculate_GPA();
    int get_Number_Of_Courses();
    bool save_students(string filename);
    void Card();
};
