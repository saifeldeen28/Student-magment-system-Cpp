#include "instructor.h"

void Instructor::set_courses(Course* newCourses) {
    courses = newCourses;
}

Course* Instructor::get_courses() const {
    return courses;
}

int Instructor::get_courses_count() const {
    return course_count;
}

Instructor::Instructor() {
    set_user_type("instructor");
}

Instructor::Instructor(int id, string username, string password, Course* c, int count) : User(id, username, password) {
    courses = c;
    course_count = count;
    set_user_type("instructor");
}

void Instructor::add_course(Course& course) {
    if (course_count >= 5) {
        cout << "Cannot add more than 5 courses." << endl;
        return;
    }
    for (int i = 0; i < course_count; i++) {
        if (courses[i].get_code() == course.get_code()) {
            cout << "Course already exists." << endl;
            return;
        }
    }
    course.add_instructor(get_id());
    Course* new_courses = new Course[course_count + 1];

    for (int i = 0; i < course_count; i++) {
        new_courses[i] = courses[i];
    }
    new_courses[course_count] = course;
    courses = new_courses;
    course_count++;
    cout << " added to list of courses successfully." << endl;
}

void Instructor::remove_course(Course& course) {
    for (int i = 0; i < course_count; i++) {
        if (courses[i].get_code() == course.get_code()) {
            Course* new_courses = new Course[course_count - 1];  // Step 1: Allocate smaller array

            for (int j = 0; j < i; j++)                          // Step 2: Copy elements before `i`
                new_courses[j] = courses[j];

            for (int j = i + 1; j < course_count; j++)           // Step 3: Copy elements after `i`
                new_courses[j - 1] = courses[j];

            courses = new_courses;                    // Step 5: Update pointer
            course_count--;                                      // Step 6: Update count

            cout << " removed from list of courses successfully." << endl;
            break;
        }
    }
}

void Instructor::set_grade(Course& course, Student &s, int grade) {
    course.set_grade(s.get_id(), grade);
}

double Instructor::max_grade(const Course& course) {
    int* grades = course.get_grades();
    int maximum = -1;
    for (int i = 0; i < course.get_number_of_students(); i++) {
        if (grades[i] > maximum) {
            maximum = grades[i];
        }
    }
    return maximum;
}

double Instructor::min_grade(const Course& course) {
    int* grades = course.get_grades();
    int minimum = 200;
    for (int i = 0; i < course.get_number_of_students(); i++) {
        if (grades[i] < minimum) {
            minimum = grades[i];
        }
    }
    return minimum;
}

double Instructor::avg_grade(Course& course) {
    int* grades = course.get_grades();
    double total = 0;
    for (int i = 0; i < course.get_number_of_students(); i++) {
        total += grades[i];
    }
    return total / course.get_number_of_students();
}

void Instructor::save() {
    ofstream file("instructors.txt", ios::app);

    if (!file.is_open()) {
        cout << "Failed to open file" << endl;
        return;
    }

    file << get_id() << " " << get_username() << " " << get_password() << " " << get_courses_count() << " ";

    for (int i = 0; i < course_count; ++i) {
        file << courses[i].get_code() << " ";
    }

    file.close();
    cout << "Instructor data saved successfully.";
} 