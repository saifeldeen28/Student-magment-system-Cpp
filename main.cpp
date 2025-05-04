#include <iostream>
#include <vector>
#include "User.h"
#include "Course.h"
#include "student.h"
using namespace std;
int main() {
    //authentication
    User u1(1,"s","2");
    vector<int> grades{1,2,35,6,7};
    vector<int> ids {1,2,35,6,7};
    vector<int> instructors_ids {1,2,35,6,7};

    Course c1("n",1,3,grades,ids,instructors_ids);
    Student s1(1,"s","2");



    return 0;
}