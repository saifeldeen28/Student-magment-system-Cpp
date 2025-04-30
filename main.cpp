#include <iostream>
#include <vector>
#include "User.h"
#include "Course.h"
using namespace std;
int main() {
    //authentication
    User u1(1,"s","2");
    vector<int> id {1,2};
    vector<int> all{1,2,35,6,7};
    vector<int> al{1,2,35,6,7};

    Course c1("n",1,3,al);
    cout<<c1.set_instructors_ids(id,all);
    c1.print_instructors_ids();



    return 0;
}