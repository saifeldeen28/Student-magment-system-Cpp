
#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <vector>
#include "Course.h"
#include "User.h"
using namespace std ;
class Student : public User {
public:
    vector<Course*> Registered_Courses ;
    vector<int> Grades ;
    int MAX_COURSES = 6 ;
    int id;
    string password;
    string username;
    Student(string username, string password, int id,vector<Course> &courses, vector<grades> &grades):User(id,password,username,courses , grades){
        
    }
    bool add(Course* course) {
        if (Registered_Courses.size() >= MAX_COURSES) {
            cout<< "You have reached the maximum number of courses" << endl ;
            return false;
        }
        for (int i = 0; i < Registered_Courses.size(); i++) {
            if (Registered_Courses[i]->code == course->code) {
                cout<< "Already registered for course ID: " << course->code<< endl ;
                return false;
            }
        }

        Registered_Courses.push_back(course);
        Grades.push_back(0);

        cout<< "Successfully registered for course ID: " << course->code << endl ;
        return true ;
    }
    bool drop(int courseID) {
        for (int i = 0 ; i < Registered_Courses.size() ; i++) {
            if (Registered_Courses[i]->code == courseID) {
                Registered_Courses.erase(Registered_Courses.begin() + i);
                if (i < Grades.size()) {
                    Grades.erase(Grades.begin() + i);
                }
                cout<< "Successfully dropped course ID:"<< courseID << endl  ;
                return true;
            }
        }

        cout<< "Course ID " << courseID << " not found in your registered courses   " << endl ;
        return false;
    }
    void viewGrades() {
        if (Registered_Courses.empty()) {
            cout<< "You are not registered in any courses" << endl ;
            return;
        }

        cout << "Your Grades:" << endl ;
        for (int i = 0; i < Registered_Courses.size(); i++) {
            cout<< "Course: " << Registered_Courses[i]->name << " ID: " << Registered_Courses[i]->code<< "Grade: " << Grades[i] << endl ;
        }
    }
    void averageGrade() {
        if (Grades.empty()) {
            cout<< "No grades available to calculate average." << endl ;
            return ;
        }

         sum = 0;
        for (int i = 0 ; i < Grades.size() ; i++) {
            sum += Grades[i];
        }

        double average = (double)sum / Grades.size() ;
        cout << "Average grade: " << average << endl ;
    }

};

#endif // STUDENT_H

