#include <iostream>
#include <vector>

#include "admin.h"
#include "User.h"
#include "Course.h"
#include "instructor.h"
#include "student.h"
using namespace std;
int main() {
    Student s1(1,"saif","123");
    Student s2(2,"joe","456");
    Student s3(3,"karim","789");
    Student s4(4,"mostafa","789");
    int student_ids[2]={1,2};
    int student_grades[2]={90,91};
    int instructor_ids[1]={1};
    Course c1("physics",1,3,student_ids,student_grades,2,instructor_ids,1);
    //student and course testing
    c1.add_student(s3.getId(),80);
    c1.print_grades();
    c1.drop_stuent(s1.getId());
    c1.print_grades();
    s4.add(c1,99);
    c1.print_grades();
    s4.viewGrades();
    s4.drop(c1);
    c1.print_grades();
    cout<<endl<<endl;
    //instructor testing
    Course* instructor_courses = {&c1};
    Instructor i1(1,"hassan","123",instructor_courses,1);
    Student s5(5,"adham","123");

    cout<<i1.avg_grade(c1)<<endl;
    cout<<i1.min_grade(c1)<<endl;
    s5.add(c1);
    c1.add_student(s5.getId(),70);
    i1.set_grade(c1,s5,99);
    cout<<i1.max_grade(c1)<<endl;
    s5.viewGrades();
    i1.remove_course(c1);


    return 0;
}