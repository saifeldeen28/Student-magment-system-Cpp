
#include <iostream>
#include "student.h"
#include "Course.h"
#include "User.h"
using namespace std ;
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

    cout << endl << "GPA: " << calculate_GPA() << endl ;
    cout << " ======================================== " << endl ;
}
void performance_C(Course &c) {
    cout << "========================================" << endl;
    cout << "         Course Performance" << endl;
    cout << "========================================" << endl;
    cout<< "Course Report : "<< c.get_name() << endl ;
    cout << '------------------------------' <<endl ;
    cout<<"Total Students : "<< c.get_number_of_students() << endl ;
    cout<<"Average Grade : " << c.get_Average_Grade() ;
    cout <<"Highest Grade : "<< c.get_highest_grade() << endl ;
    cout<< "Lowest Grade : "<< c.get_lowest_grade() << endl ;
    cout<< "Passing Students : "<< c.get_passing_students() << endl ;
    cout<< "Failing Students : "<< c.get_failing_students() << endl ;
    cout << '------------------------------' <<endl ;
    cout << " Top Students : " << endl ;
    cout << "========================================" << endl ;


}
};

