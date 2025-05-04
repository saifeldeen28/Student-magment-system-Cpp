#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include "Course.h"
#include "User.h"
using namespace std;

class Student : public User {
private:
    const int MAX_COURSES = 6;
    Course registered_courses[MAX_COURSES]; // Stored by value
    int course_count;

public:
    Student(int id, string username, string password) : User(id , username , password){
            course_count = 0 ;
    }

    // Add a course
    bool add(Course course) {


        if (course_count >= MAX_COURSES)
        {
            cout<< "You have reached the maximum number of courses" << endl;
            return false;
        }

        // Check if already registered
        for (int i = 0 ; i < course_count ; i++)
        {
            if (registered_courses[i].name == Course.name)
            {
                cout << "Already registered for course " << course.name << endl;
                return false;
            }
        }

        // Register student in course
        Course.student_ids[Course.student_ids.size()] = id ;
        Course.grades[Course.grades.size()] = 0 ;
        registered_courses[course_count++] = course ;
        cout << " Successfully registered for course: " << course.name << endl ;
        return true ;
    }

    bool drop(course c) {

    }

    void viewGrades() const {
        if (course_count == 0)
        {
            cout << "You are not registered in any courses" << endl ;
            return ;
        }

        cout << "Your Grades :" << endl;
        for (int i = 0; i < course_count ; i++ )
        {
            cout<< "Your Course : "registered_courses[i] << "Your Grade : "<< Course.grades[i] ;
        }


    }

    void averageGrade()
       {

        if (course_count == 0) {
            cout<< "No grades available to calculate average" << endl ;
            return ;
        }

        double sum = 0;

        for (int i = 0 ; i < course_count ; i++)
        {

            sum+= registered_courses[i] ;
            cout << sum / course_count ;
        }


    int get_Number_Of_Courses()
    {
        return course_count ;
    }

};

#endif // STUDENT_H
