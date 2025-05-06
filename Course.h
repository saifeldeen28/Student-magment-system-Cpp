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
    string name;
    int code;
    vector<int> instructors_ids;
    int credits;
    vector<int> grades;
    vector<int> student_ids;
public:
    // constructor
    Course(){}
    Course(string name,const int code, int credits, const vector<int> &grades, const vector<int> &student_ids, const vector<int> &instructors_ids)
        : name(move(name)), code(code), credits(credits), grades(grades),student_ids(student_ids), instructors_ids(instructors_ids) {}


    // Setters
    void setName(const std::string& newName) { name = newName; }
    void setCode(int newCode) { code = newCode; }
    void setInstructorsIds(const std::vector<int>& newInstructorsIds) { instructors_ids = newInstructorsIds; }
    void setCredits(int newCredits) { credits = newCredits; }
    void setGrades(const std::vector<int>& newGrades) { grades = newGrades; }
    void setStudentIds(const std::vector<int>& newStudentIds) { student_ids = newStudentIds; }

    // Getters
    string getName() const { return name; }
    int getCode() const { return code; }
    vector<int> getInstructorsIds() const { return instructors_ids; }
    int getCredits() const { return credits; }
    vector<int> getGrades() const { return grades; }
    vector<int> getStudentIds() const { return student_ids; }


    //Functions
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
    int getGrade(int id) {
        for (int i = 0; i < student_ids.size(); i++) {
            if (student_ids.at(i) == id) {
                return grades[i]; // Directly return the grade if ID is found
            }
        }
        return -1; // No student found
    }
    void setGrade(int id,int grade) {
        for (int i = 0; i < student_ids.size(); i++) {
            if (student_ids.at(i) == id) {
                grades[i] = grade;
                return;
            }
        }
    }
};

#endif //COURSE_H
