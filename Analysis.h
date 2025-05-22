
#include <iostream>
#include "Course.h"
#include "User.h"
#include "student.h"
using namespace std;
void Card() {
    cout << "========================================" << endl;
    cout << "           STUDENT CARD"<< endl;
    cout << "----------------------------------------" << endl;
    cout << "ID           : " <<get_id()<< endl ;
    cout << "Username     : " <<get_username() << endl ;
    cout << "Password     : " << get_password() <<endl ;
    cout << "Course Count : " <<course_count << endl;
    cout << endl;

    if (course_count == 0) {
        cout << "No registered courses." << endl;
    } 
    else {
        cout << "Registered Courses:" << endl;
        for (int i = 0 ; i < course_count ; i++) {
            Course* course = registered_courses[i]  ;
            cout << " | Code: " << course->get_code()
                 << " | Name: " << course-> get_name()
                 << " | Grade: " << course-> get_grade(get_id()) << endl ;
        }
    }

    cout << endl << "GPA: " << calculate_GPA() << endl ;
    cout << " ======================================== " << endl ;
}
