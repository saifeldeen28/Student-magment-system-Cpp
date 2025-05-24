//
// Created by saidn on 5/1/2025.
//

#ifndef COURSE_H
#define COURSE_H
#include <string>
#include <iostream>
#include <fstream>
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
    Course(string name, const int code, int credits, int* instructors_ids, int number_of_instructors, int* student_ids=nullptr, int* grades=nullptr, int number_of_students=0)
    : name(move(name)), code(code), credits(credits), number_of_students(number_of_students), number_of_instructors(number_of_instructors)
    {
        // Initialize student arrays even if they're empty
        this->student_ids = new int[number_of_students > 0 ? number_of_students : 1];
        this->grades = new int[number_of_students > 0 ? number_of_students : 1];
        
        // Only copy if there are students and the arrays are provided
        if (number_of_students > 0 && student_ids != nullptr && grades != nullptr) {
            for (int i = 0; i < number_of_students; i++) {
                this->student_ids[i] = student_ids[i];
                this->grades[i] = grades[i];
            }
        }

        // Initialize instructor arrays
        this->instructors_ids = new int[number_of_instructors > 0 ? number_of_instructors : 1];
        
        // Only copy if there are instructors and the array is provided
        if (number_of_instructors > 0 && instructors_ids != nullptr) {
            for (int i = 0; i < number_of_instructors; i++) {
                this->instructors_ids[i] = instructors_ids[i];
            }
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
        if (grade < 0 || grade > 100) {
            cout << "Invalid grade. Please enter a value between 0 and 100." << endl;
            return;
        }
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
    bool save()
    {
        ofstream file("courses.txt", ios::app) ;  // Append mode
        if (!file.is_open()) {
            cout << "Failed to open courses.txt" << endl;
            return false ;
        }

        file << code << " " << name << " " << credits << " " << number_of_instructors;

        for (int i = 0; i < number_of_instructors; i++) {
            file << " " << instructors_ids[i];
        }

        file << endl;
        file.close();

        return true;
    }

    void add_instructor(int id) {
        int* new_instructors_ids = new int[number_of_instructors + 1];

        for (int i = 0; i < number_of_instructors; i++) {
            new_instructors_ids[i] = instructors_ids[i];
        }

        new_instructors_ids[number_of_instructors] = id;
        number_of_instructors++;

        instructors_ids = new_instructors_ids;  // Assign new array
    }

    double get_average_grade()
    {
        if (number_of_students == 0) return 0.0 ;
        int sum = 0 ;
        for (int i = 0 ; i < number_of_students ; i++)
        {
            sum += grades[i] ;
        }
        return static_cast <double> (sum) / number_of_students ;
    }

    int get_highest_grade()
    {
        if (number_of_students == 0) return -1 ;
        int highest = grades[0] ;
        for (int i = 1; i < number_of_students; i++)
            {
            if (grades[i] > highest)
                {
                highest = grades[i];
            }
        }
        return highest;
    }

    int get_lowest_grade()
    {
        if (number_of_students == 0) return -1 ;
        int lowest = grades[0] ;
        for (int i = 1; i < number_of_students; i++)
            {
            if (grades[i] < lowest)
                {
                lowest = grades[i];
            }
        }
        return lowest ;
    }

    int get_passing_students()
    {
        int count = 0 ;
        for (int i = 0; i < number_of_students; i++)
            {
            if (grades[i] >= 50) {
                count++ ;
            }
        }
        return count;
    }

    int get_failing_students()  {
        return    number_of_students - get_passing_students() ;
    }


    void performance_C() {
        cout << "========================================" << endl;
        cout << "         Course Performance            " << endl;
        cout << "========================================" << endl;
        cout<< "Course Report : " << get_name() << endl ;
        cout << "------------------------------" <<endl ;
        cout<<"Total Students    : "<< get_number_of_students() << endl ;
        cout<<"Average Grade     : " << get_average_grade() <<endl;
        cout <<"Highest Grade    : "<< get_highest_grade() << endl ;
        cout<< "Lowest Grade     : "<< get_lowest_grade() << endl ;
        cout<< "Passing Students : "<< get_passing_students() << endl ;
        cout<< "Failing Students : "<< get_failing_students() << endl ;
        cout << "========================================" << endl ;


    }
};

#endif //COURSE_H
