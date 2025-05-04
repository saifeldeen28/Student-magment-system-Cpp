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
    Course(string name,const int code, int credits, const vector<int> grades)
        : name(move(name)), code(code), credits(credits), grades(grades) {}

    // Improved instructor ID setter function
    bool set_instructors_ids(const vector<int>& ids, const vector<int>& all_ids) {
        for (int id : ids) {
            bool exists = false;
            for (int valid_id : all_ids) {
                if (id == valid_id) {
                    exists = true;
                    break; // Found the ID, no need to keep checking
                }
            }
            if (!exists) {
                return false; // If any ID doesn't exist, return false immediately
            }
        }
        instructors_ids = ids;
        return true;
    }
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
};

#endif //COURSE_H
