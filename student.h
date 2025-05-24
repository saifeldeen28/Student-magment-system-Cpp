#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <fstream>
#include "Course.h"
#include "User.h"
using namespace std;
class Student : public User {
private:
    static const int MAX_COURSES = 6 ;
    Course* registered_courses[MAX_COURSES] ; 
    int course_count;

public:
    Student() {
        set_user_type("student") ;
        course_count = 0 ;
        for (int i = 0; i < MAX_COURSES; i++) {
            registered_courses[i] = nullptr ; // Initialize pointers to NULL
        }
    }

    Student(int id, string username, string password) : User(id, username, password) {
        set_user_type("student");
        course_count = 0 ;
        for (int i = 0; i < MAX_COURSES; i++) {
            registered_courses[i] = nullptr; // Initialize pointers
        }
    }

    bool add(Course& course , int grade = 0) {
        if (course_count >= MAX_COURSES) {
            cout << "You cant register for more than " << MAX_COURSES << " courses " << endl ;
            return false ;
        }

        if (!course.add_student(get_id(), grade)) {
            cout << " Couldn't add student to the course " << endl ;
            return false;
        }

        registered_courses[course_count] = &course ; 
        course_count++;
        cout << "Successfully registered for " << course.get_name() 
             << " with student ID: " << get_id() << endl ;
        return true;
    }

    bool drop(Course& course) {
        if (&course == nullptr) {
            return false;  // Handle null case safely
        }
        
        bool found = false ;
        for (int i = 0; i < course_count; i++) {
            if (registered_courses[i] != nullptr && 
                registered_courses[i]->get_code() == course.get_code()) {
                found = true ;
                course.drop_student(get_id());

                for (int j = i; j < course_count - 1; j++) {
                    registered_courses[j] = registered_courses[j + 1]; // Shift courses left
                }

                registered_courses[course_count - 1] = nullptr;
                course_count--;

                cout << "Course dropped successfully " << endl;
                break;
            }
        }
        if (!found) {
            // No need to print an error if called by the system during course removal
            return false;
        }

        return true;
    }

    void view_grades() {
        if (course_count == 0) {
            cout << "+--------------------------------------+\n";
            cout << "| You are not registered in any courses |\n";
            cout << "+--------------------------------------+\n";
            return;
        }

        cout << "+--------------------------------------+\n";
        cout << "|            YOUR GRADES              |\n";
        cout << "+--------------------------------------+\n";
        for (int i = 0; i < course_count; i++) {
            string courseName = registered_courses[i]->get_name();
            int grade = registered_courses[i]->get_grade(get_id());
            
            cout << "| Course: " << courseName;
            // Add padding for course name alignment
            int padding1 = 30 - courseName.length();
            for (int j = 0; j < padding1; j++) cout << " ";
            cout << "|\n";
            
            cout << "| Grade: " << grade;
            // Add padding for grade alignment
            int padding2 = 31 - to_string(grade).length();
            for (int j = 0; j < padding2; j++) cout << " ";
            cout << "|\n";
            
            cout << "+--------------------------------------+\n";
        }
    }
    
    void average_grade() {
        if (course_count == 0) {
            cout << "+--------------------------------------+\n";
            cout << "| No grades available for average      |\n";
            cout << "+--------------------------------------+\n";
            return;
        }

        double sum = 0;
        for (int i = 0; i < course_count; i++) {
            sum += registered_courses[i]->get_grade(get_id());
        }
        
        double avg = sum / course_count;
        cout << "+--------------------------------------+\n";
        cout << "| Average Grade: " << avg;
        // Add padding for average alignment
        int padding = 26 - to_string((int)avg).length();
        if (avg - (int)avg > 0.001) padding -= 4; // Adjust for decimal places
        for (int i = 0; i < padding; i++) cout << " ";
        cout << "|\n";
        cout << "+--------------------------------------+\n";
    }

    double calculate_gpa() {
        if (course_count == 0) {
            cout << "No registered courses. GPA is 0.0" << endl;
            return 0.0;
        }

        double total_gpa_points = 0.0;
        int total_credits = 0;

        for (int i = 0; i < course_count; i++) {
            int grade = registered_courses[i]->get_grade(get_id());
            int credits = registered_courses[i]->get_credits();

            double gpa_value;

            if (grade >= 90) gpa_value = 4.0;
            else if (grade >= 85) gpa_value = 3.7;
            else if (grade >= 80) gpa_value = 3.3;
            else if (grade >= 75) gpa_value = 3.0;
            else if (grade >= 70) gpa_value = 2.7;
            else if (grade >= 65) gpa_value = 2.3;
            else if (grade >= 60) gpa_value = 2.0;
            else if (grade >= 55) gpa_value = 1.7;
            else if (grade >= 50) gpa_value = 1.3;
            else if (grade >= 45) gpa_value = 1.0;
            else gpa_value = 0.0;

            total_gpa_points += gpa_value * credits;
            total_credits += credits;
        }

        double gpa = (total_credits > 0) ? total_gpa_points / total_credits : 0.0;
        return gpa;
    }

    int get_number_of_courses() {
        return course_count;
    }
void save() override
{
    ofstream file("students.txt", ios::app) ;  // Append mode
    if (!file.is_open()) {
        cout << "The file os opened " << "students.txt" << endl;
        return ;
    }

    file << get_id() << " " << get_username() << " "<<get_password() << " " << course_count ;

    for (int i = 0; i < course_count; i++) {
        file << " " << registered_courses[i]->get_code()
             << " " << registered_courses[i]->get_grade(get_id()) ;
    }

    file << endl;
    file.close();

    return;
}

    void Card() {
        cout << "========================================" << endl;
        cout << "           STUDENT CARD" << endl;
        cout << "----------------------------------------" << endl;
        cout << "ID           : " << get_id() << endl;
        cout << "Username     : " << get_username() << endl;
        cout << "Password     : " << get_password() << endl;
        cout << "Course Count : " << course_count << endl;
        cout << endl;

        if (course_count == 0) {
            cout << "No registered courses." << endl;
        } else {
            cout << "Registered Courses:" << endl;
            for (int i = 0; i < course_count; i++) {
                Course *course = registered_courses[i];
                cout << " | Code: " << course->get_code()
                        << " | Name: " << course->get_name()
                        << " | Grade: " << course->get_grade(get_id()) << endl;
            }
        }

        cout << endl << "GPA: " << calculate_gpa() << endl ;
        cout << " ======================================== " << endl ;
    }
};

#endif // STUDENT_H
