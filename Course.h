//
// Created by saidn on 5/1/2025.
//

#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <utility>
#include <vector>
using namespace std;

class Course {
public:
    string name;
    int code;
    vector<int> instructors_ids;
    int credits;
    vector<int> grades;
    vector<int> student_ids;

    // Improved constructor with initializer list
    Course(string name,const int code, int credits, const vector<int> &grades, const vector<int> &student_ids, const vector<int> &instructors_ids)
        : name(move(name)), code(code), credits(credits), grades(grades),student_ids(student_ids), instructors_ids(instructors_ids) {}

        Course(){};


    void print_grades() {
        for (int i = 0; i < grades.size(); i++) {
            cout<<grades.at(i)<<endl;
        }
    }
    void print_instructors_ids() {
        for (int i = 0; i < instructors_ids.size(); i++) {
            cout<<instructors_ids.at(i)<<endl;
        }
    }
    int getGrade(int id){
        int flag=0;
        for (int i = 0; i < student_ids.size(); i++) {
            if (student_ids.at(i) == id) {
                flag=1;
            }
        }
        if (flag==0) {
            return -1;//no student found
        }
        int index;
        for(int i=0 ; i<student_ids.size();i++){
            if(id==student_ids[i]){
                index=i;
                break;
            }
        }
        return grades[index];
    }
};

#endif //COURSE_H
