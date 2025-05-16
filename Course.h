//
// Created by saidn on 5/1/2025.
//

#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <utility>

using namespace std;

class Course {
    string name;
    int code;
    int *instructors_ids;
    int number_of_instructors;
    int credits;
    int *grades;
    int *student_ids;
    int number_of_students;
public:
    // constructor
    Course(){}
    Course(string name, const int code, int credits, int* student_ids, int* grades, int number_of_students, int* instructors_ids, int number_of_instructors)
    : name(move(name)), code(code), credits(credits), number_of_students(number_of_students), number_of_instructors(number_of_instructors)
    {
        this->student_ids = new int[number_of_students];
        this->grades = new int[number_of_students];
        for (int i = 0; i < number_of_students; i++) {
            this->student_ids[i] = student_ids[i];
            this->grades[i] = grades[i];
        }

        this->instructors_ids = new int[number_of_instructors];
        for (int i = 0; i < number_of_instructors; i++) {
            this->instructors_ids[i] = instructors_ids[i];
        }
    }





    // Setters
    void set_name(const std::string& newName) { name = newName; }
    void set_code(int newCode) { code = newCode; }
    void set_instructors_ids(int* ids) { instructors_ids = ids; }
    void set_credits(int newCredits) { credits = newCredits; }
    void set_grades(int* g) { grades = g; }
    void set_student_ids(int* stu,int n) { student_ids = stu; number_of_students = n; }


    // Getters
    string get_name() const { return name; }
    int get_code() const { return code; }
    int* get_instructors_ids() const { return instructors_ids; }
    int get_credits() const { return credits; }
    int* get_grades() const { return grades; }
    int* get_student_ids() const { return student_ids; }
    int get_number_of_students() const { return number_of_students; }

    //Functions
    void print_grades() {
        for (int i = 0; i < number_of_students; i++) {
            cout<<grades[i]<<endl;
        }
    }
    void print_instructors_ids() {
        for (int i = 0; i < number_of_instructors; i++) {
            cout<<instructors_ids[i]<<endl;
        }
    }
    int get_grade(int id) {
        for (int i = 0; i < number_of_students; i++) {
            if (student_ids[i] == id) {
                return grades[i]; // Directly return the grade if ID is found
            }
        }
        return -1; // No student found
    }
    void set_grade(int id,int grade) {
        for (int i = 0; i < number_of_students; i++) {
            if (student_ids[i] == id) {
                grades[i] = grade;
                return;
            }
        }
    }
    bool add_student(int id,int grade=0) {
        for (int i = 0; i < number_of_students; i++) {
            if (student_ids[i] == id) {
                return false;
            }
        }
        int* new_student_ids = new int[number_of_students+1];
        int* new_grades = new int[number_of_students+1];
        for (int i = 0; i < number_of_students; i++) {
            new_student_ids[i] = student_ids[i];
            new_grades[i] = grades[i];
        }
        new_student_ids[number_of_students] = id;
        new_grades[number_of_students] = grade;

        delete [] student_ids;
        delete [] grades;

        number_of_students++;

        student_ids = new_student_ids;
        grades = new_grades;

        return true;
    }
    bool drop_student(int id) {
        for (int i = 0; i < number_of_students; i++) {
            if (student_ids[i] == id) {
                for (int j = i; j < number_of_students-1; j++) {
                    student_ids[j] = student_ids[j+1];
                    grades[j] = grades[j+1];
                }
                number_of_students--;
                return true;
            }
        }
        return false;
    }



    // Copy assignment operator
    Course& operator=(const Course& other) {
        // Self-assignment check
        if (this == &other) {
            return *this;
        }

        // Copy primitive types
        name = other.name;
        code = other.code;
        credits = other.credits;
        number_of_students = other.number_of_students;
        number_of_instructors = other.number_of_instructors;

        // Free existing memory
        delete[] instructors_ids;
        delete[] grades;
        delete[] student_ids;

        // Allocate new memory and deep copy arrays
        instructors_ids = new int[number_of_instructors];
        for (int i = 0; i < number_of_instructors; i++) {
            instructors_ids[i] = other.instructors_ids[i];
        }

        student_ids = new int[number_of_students];
        grades = new int[number_of_students];
        for (int i = 0; i < number_of_students; i++) {
            student_ids[i] = other.student_ids[i];
            grades[i] = other.grades[i];
        }

        // Return reference to current object
        return *this;
    }
};

#endif //COURSE_H
