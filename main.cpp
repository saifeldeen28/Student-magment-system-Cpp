#include <iostream>
#include <vector>
#include "User.h"
#include "Course.h"
#include "instructor.h"
#include "student.h"
using namespace std;
int main() {
    //authentication
    User u1(1,"s","2");
    vector<int> grades{1,2,35,6,7};
    vector<int> ids {1,2,35,6,7};
    vector<int> instructors_ids {1,2,35,6,7};


    Course c1("n",1,3,grades,ids,instructors_ids);
    Course c2("m",1,3,grades,ids,instructors_ids);
    vector<Course> courses={c1,c2};
    Student s1(1,"s","2");
    Instructor i1(10,"x","123",courses);
    s1.add(c1);
    s1.add(c2);
    s1.viewGrades();
    cout<<i1.avg_grade(c1)<<endl;
    cout<<i1.max_grade(c1)<<endl;
    cout<<i1.min_grade(c1)<<endl;
    i1.remove_course(c2);
    cout<<i1.getCourses().size()<<endl;
    i1.add_course(c2);
    cout<<i1.getCourses().size()<<endl;
    cout<<c1.getGrade(s1.getId())<<endl;
    i1.set_grade(c1,s1,2);
    cout<<c1.getGrade(s1.getId())<<endl;



    return 0;
}