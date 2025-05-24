#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include "User.h"
#include "Course.h"
#include "student.h"
#include "instructor.h"
#include <fstream>

using namespace std;

class Administrator : public User {
private:
    Course course_list[20];  // Local copy of courses
    int course_count;
    
    // Helper function to sync course list
    void sync_course_list() {
        for (int i = 0; i < course_count; i++) {
            course_list[i] = outer_course_list[i];
        }
    }
    
    Course* outer_course_list;  // Pointer to the external course list

public:
    Administrator(int id, string username, string password, Course* external_courses = nullptr, int count = 0)
        : User(id, username, password), course_count(count), outer_course_list(external_courses) {
        set_user_type("admin");
        if (external_courses != nullptr) {
            for (int i = 0; i < count; i++) {
                course_list[i] = external_courses[i];
            }
        }
    }

    void set_course_count(int count) {
        course_count = count;
    }

    void set_course_list(Course* list) {
        outer_course_list = list;
        for (int i = 0; i < course_count; i++) {
            course_list[i] = list[i];
        }
    }

    void view_students(const Student* student_list, int student_count) {
        cout << "\n=== Student List ===\n";
        if (student_count == 0) {
            cout << "No students registered.\n";
            return;
        }
        
        for (int i = 0; i < student_count; i++) {
            cout << (i+1) << ". Student: " << student_list[i].get_username() 
                 << " | ID: " << student_list[i].get_id() << endl;
        }
    }
    
    void view_instructors(const Instructor* instructor_list, int instructor_count) {
        cout << "\n=== Instructor List ===\n";
        if (instructor_count == 0) {
            cout << "No instructors registered.\n";
            return;
        }
        
        for (int i = 0; i < instructor_count; i++) {
            cout << (i+1) << ". Instructor: " << instructor_list[i].get_username()
                 << " | ID: " << instructor_list[i].get_id() << endl;
        }
    }

    void add_student(int id, string username, string password, Student* student_list,
                    int& student_count) {
        // Check if student with same ID or username exists
        for (int i = 0; i < student_count; i++) {
            if (student_list[i].get_id() == id || student_list[i].get_username() == username) {
                cout << "Student with same ID or username already exists" << endl;
                return;
            }
        }

        student_list[student_count] = Student(id, username, password);
        student_count++;

        cout << "Student added successfully" << endl;
    }

    void add_instructor(int id, string username, string password, Instructor* instructor_list,
                       int& instructor_count) {
        // Check if instructor with same ID or username exists
        for (int i = 0; i < instructor_count; i++) {
            if (instructor_list[i].get_id() == id || instructor_list[i].get_username() == username) {
                cout << "Instructor with same ID or username already exists" << endl;
                return;
            }
        }

        Course* courses = nullptr;
        instructor_list[instructor_count] = Instructor(id, username, password, courses, 0);
        instructor_count++;

        cout << "Instructor added successfully" << endl;
    }

    void remove_student(Student* student_list, int& student_count, int id) {
        bool found = false;
        for (int i = 0; i < student_count; i++) {
            if (student_list[i].get_id() == id) {
                // Shift remaining elements left
                for (int j = i; j < student_count - 1; j++) {
                    student_list[j] = student_list[j + 1];
                }
                student_count--;
                cout << "Student removed successfully" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Student not found" << endl;
        }
    }

    void remove_instructor(Instructor* instructor_list, int& instructor_count, int id) {
        bool found = false;
        for (int i = 0; i < instructor_count; i++) {
            if (instructor_list[i].get_id() == id) {
                for (int j = i; j < instructor_count - 1; j++) {
                    instructor_list[j] = instructor_list[j + 1];
                }
                instructor_count--;
                cout << "Instructor removed successfully" << endl;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Instructor not found" << endl;
        }
    }

    void add_course(const string &name, int code, int credits,
                   int* instructors_ids, int num_instructors,
                   Instructor* instructor_list, int instructor_count) {
        
        for (int i = 0; i < course_count; i++) {
            if (course_list[i].get_code() == code) {
                cout << "Course with same code already exists" << endl;
                return;
            }
        }

        Course new_course(name, code, credits, instructors_ids, num_instructors);
        course_list[course_count] = new_course;
        outer_course_list[course_count] = new_course;  // Update external list
        course_count++;
        
        // Find and update the instructors who teach this course
        for (int i = 0; i < num_instructors; i++) {
            int instructor_id = instructors_ids[i];
            for (int j = 0; j < instructor_count; j++) {
                if (instructor_list[j].get_id() == instructor_id) {
                    instructor_list[j].add_course(new_course);
                    break;
                }
            }
        }
        
        cout << "Course added successfully" << endl;
    }

    void remove_course(int code, Student* student_list, int student_count, 
                      Instructor* instructor_list, int instructor_count) {
        bool found = false;
        Course* course_to_remove = nullptr;
        int course_index = -1;
        
        // Find the course
        for (int i = 0; i < course_count; i++) {
            if (course_list[i].get_code() == code) {
                course_to_remove = &course_list[i];
                course_index = i;
                found = true;
                break;
            }
        }
        
        if (!found) {
            cout << "Course not found" << endl;
            return;
        }

        // Remove course from all students that have registered for it
        for (int i = 0; i < student_count; i++) {
            student_list[i].drop(*course_to_remove);
        }
        
        // Remove course from all instructors that teach it
        for (int i = 0; i < instructor_count; i++) {
            instructor_list[i].remove_course(*course_to_remove);
        }
        
        // Remove the course from both lists
        for (int j = course_index; j < course_count - 1; j++) {
            course_list[j] = course_list[j + 1];
            outer_course_list[j] = outer_course_list[j + 1];
        }
        course_count--;
        
        cout << "Course removed successfully" << endl;
        
        // Update files
        ofstream courseFile("courses.txt", ios::trunc);
        courseFile.close();
        
        for (int i = 0; i < course_count; i++) {
            course_list[i].save();
        }
        
        ofstream studentFile("students.txt", ios::trunc);
        studentFile.close();
        
        for (int i = 0; i < student_count; i++) {
            student_list[i].save();
        }
        
        ofstream instructorFile("instructors.txt", ios::trunc);
        instructorFile.close();
        
        for (int i = 0; i < instructor_count; i++) {
            instructor_list[i].save();
        }
    }

    Course* get_course_list() const {
        return outer_course_list;  // Return the external list
    }

    int get_course_count() const {
        return course_count;
    }

    void display_students_by_GPA(Student* s, int students_count) {
        double minGPA, maxGPA;

        cout << "Enter the minimum GPA: ";
        cin >> minGPA;

        cout << "Enter the maximum GPA: ";
        cin >> maxGPA;

        if (minGPA > maxGPA || minGPA < 0.0 || maxGPA > 4.0) {
            cout << "Invalid GPA range entered. Please enter values between 0.0 and 4.0." << endl;
            return;
        }

        cout << "Students with GPA between " << minGPA << " and " << maxGPA << ":" << endl;

        bool found = false;

        for (int i = 0; i < students_count; i++) {
            double GPA = s[i].calculate_gpa();

            if (GPA >= minGPA && GPA <= maxGPA) {
                cout << s[i].get_username() << "  GPA: " << GPA << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No students found in this GPA range." << endl;
        }
    }

    void save() override {
        // Admin doesn't need to be saved
    }

    void view_courses() const {
        cout << "\n=== Course List ===\n";
        if (course_count == 0) {
            cout << "No courses available.\n";
            return;
        }
        
        for (int i = 0; i < course_count; i++) {
            cout << (i+1) << ". Course: " << course_list[i].get_name() 
                 << " | Code: " << course_list[i].get_code()
                 << " | Credits: " << course_list[i].get_credits() 
                 << " | Students: " << course_list[i].get_number_of_students() << endl;
        }
        cout << endl;
    }
};

#endif //ADMIN_H
