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
    s1.add(c1);
    s1.add(c2);
    s1.viewGrades();




    return 0;
}