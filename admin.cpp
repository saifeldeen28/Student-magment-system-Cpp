#include "admin.h"

Administrator::Administrator(int id, string username, string password, Course l[20], int count)
: User(id, username, password), course_count(count) {
    if (l!=nullptr) {
        for (int i = 0; i < 20; i++) {
            course_list[i] = l[i]; // Copy each element individually
        }
    }
}

void Administrator::view_students(const Student* student_list, int student_count) {
    cout << "\n=== Student List ===\n";
    if (student_count == 0) {
        cout << "No students registered.\n";
        return;
    }
    
    for (int i = 0; i < student_count; i++) {
        cout << (i+1) << ". student: " << student_list[i].get_username() 
             << " id=" << student_list[i].get_id() << endl;
    }
}

void Administrator::view_instructors(const Instructor* instructor_list, int instructor_count) {
    cout << "\n=== Instructor List ===\n";
    if (instructor_count == 0) {
        cout << "No instructors registered.\n";
        return;
    }
    
    for (int i = 0; i < instructor_count; i++) {
        cout << (i+1) << ". instructor: " << instructor_list[i].get_username() 
             << " id=" << instructor_list[i].get_id() << endl;
    }
}

void Administrator::add_student(int id, string username, string password, Student* student_list,
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

void Administrator::set_course_list(Course* list) {
    for (int i = 0; i < 20; i++) {
        course_list[i] = list[i]; // Copy each element individually
    }
}

void Administrator::add_instructor(int id, string username, string password, Instructor* instructor_list,
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

void Administrator::remove_student(Student* student_list, int& student_count, int id) {
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

void Administrator::remove_instructor(Instructor* instructor_list, int& instructor_count, int id) {
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

void Administrator::add_course(const string &name, int code, int credits,
int* instructors_ids, int num_instructors,
               Instructor* instructor_list, int instructor_count) {
    
    for (int i = 0; i < course_count; i++) {
        if (course_list[i].get_code() == code) {
            cout << "Course with same code already exists" << endl;
            return;
        }
    }

    Course new_course(name, code, credits, instructors_ids, num_instructors);
    course_list[course_count++] = new_course;
    
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

void Administrator::remove_course(int code) {
    bool found = false;
    for (int i = 0; i < course_count; i++) {
        if (course_list[i].get_code() == code) {
            // Shift remaining elements left
            for (int j = i; j < course_count - 1; j++) {
                course_list[j] = course_list[j + 1];
            }
            course_count--;
            cout << "Course removed successfully" << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Course not found" << endl;
    }
}

const Course* Administrator::get_course_list() const {
    return course_list;
}

int Administrator::get_course_count() const {
    return course_count;
} 