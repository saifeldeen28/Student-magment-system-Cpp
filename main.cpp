#include <iostream>
#include <fstream>
#include <sstream>

#include "admin.h"
#include "User.h"
#include "Course.h"
#include "instructor.h"
#include "student.h"
using namespace std;

// Helper function to find a course by code
Course* find_course_by_code(Course* course_list, int course_count, int code) {
    for (int i = 0; i < course_count; i++) {
        if (course_list[i].get_code() == code) {
            return &course_list[i];
        }
    }
    return nullptr;
}

// Helper function to find a student by ID
Student* find_student_by_id(Student* student_list, int student_count, int id) {
    for (int i = 0; i < student_count; i++) {
        if (student_list[i].get_id() == id) {
            return &student_list[i];
        }
    }
    return nullptr;
}

void show_student_main_menu(Student &student, Course* course_list, int &course_count) {
    int choice = 0;
    while (choice != 6) {
        cout << "\n=== Student Menu ===\n";
        cout << "1. Register in a new course\n";
        cout << "2. Drop a course\n";
        cout << "3. View grade in a specific course\n";
        cout << "4. View average grade across all courses\n";
        cout << "5. View registered courses\n";
        cout << "0. Log out\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int course_code;
                cout << "Enter course code to register: ";
                cin >> course_code;

                Course* course_to_add = find_course_by_code(course_list, course_count, course_code);
                if (course_to_add) {
                    student.add(*course_to_add);
                } else {
                    cout << "Course not found.\n";
                }
                break;
            }
            case 2: {
                int course_code;
                cout << "Enter course code to drop: ";
                cin >> course_code;

                Course* course_to_drop = find_course_by_code(course_list, course_count, course_code);
                if (course_to_drop) {
                    student.drop(*course_to_drop);
                } else {
                    cout << "Course not found or not registered.\n";
                }
                break;
            }
            case 3: {
                int course_code;
                cout << "Enter course code to view grade: ";
                cin >> course_code;

                Course* course = find_course_by_code(course_list, course_count, course_code);
                if (course) {
                    int grade = course->get_grade(student.get_id());
                    if (grade != -1) {
                        cout << "Your grade in " << course->get_name() << " is: " << grade << endl;
                    } else {
                        cout << "You are not registered in this course.\n";
                    }
                } else {
                    cout << "Course not found.\n";
                }
                break;
            }
            case 4: {
                student.average_grade();
                break;
            }
            case 5: {
                student.view_grades();
                break;
            }
            case 0:
                cout << "Logging out...\n";
                return;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

void show_instructor_main_menu(Instructor &instructor, Course* course_list, int &course_count, Student* student_list, int &student_count) {
    int choice = 0;
    while (choice != 8) {
        cout << "\n=== Instructor Menu ===\n";
        cout << "1. Add a course to teaching list\n";
        cout << "2. Remove a course from teaching list\n";
        cout << "3. Add or update student grades for a course\n";
        cout << "4. View max grade in a course\n";
        cout << "5. View min grade in a course\n";
        cout << "6. View average grade in a course\n";
        cout << "7. View list of courses taught\n";
        cout << "0. Log out\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int course_code;
                cout << "Enter course code to add: ";
                cin >> course_code;

                Course* course = find_course_by_code(course_list, course_count, course_code);
                if (course) {
                    instructor.add_course(*course);
                } else {
                    cout << "Course not found.\n";
                }
                break;
            }
            case 2: {
                int course_code;
                cout << "Enter course code to remove: ";
                cin >> course_code;

                Course* course = find_course_by_code(course_list, course_count, course_code);
                if (course) {
                    instructor.remove_course(*course);
                } else {
                    cout << "Course not found or not in teaching list.\n";
                }
                break;
            }
            case 3: {
                int course_code, student_id, grade;
                cout << "Enter course code: ";
                cin >> course_code;
                Course* course = find_course_by_code(course_list, course_count, course_code);
                cout << "Enter student ID: ";
                cin >> student_id;
                int flag=0;
                for (int i = 0; i < course->get_number_of_students(); i++) {
                    if (course->get_student_ids()[i] == student_id) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 0) {
                    cout << "This student isn't registered for this course ";
                    return;
                }
                cout << "Enter new grade: ";
                cin >> grade;


                if (course) {
                    Student* student = find_student_by_id(student_list, student_count, student_id);
                    if (student) {
                        instructor.set_grade(*course, *student, grade);
                        cout << "Grade updated successfully.\n";
                    } else {
                        cout << "Student not found.\n";
                    }
                } else {
                    cout << "Course not found.\n";
                }
                break;
            }
            case 4: {
                int course_code;
                cout << "Enter course code: ";
                cin >> course_code;

                Course* course = find_course_by_code(course_list, course_count, course_code);
                if (course) {
                    double max = instructor.max_grade(*course);
                    cout << "Maximum grade in course: " << max << endl;
                } else {
                    cout << "Course not found.\n";
                }
                break;
            }
            case 5: {
                int course_code;
                cout << "Enter course code: ";
                cin >> course_code;

                Course* course = find_course_by_code(course_list, course_count, course_code);
                if (course) {
                    double min = instructor.min_grade(*course);
                    cout << "Minimum grade in course: " << min << endl;
                } else {
                    cout << "Course not found.\n";
                }
                break;
            }
            case 6: {
                int course_code;
                cout << "Enter course code: ";
                cin >> course_code;

                Course* course = find_course_by_code(course_list, course_count, course_code);
                if (course) {
                    double avg = instructor.avg_grade(*course);
                    cout << "Average grade in course: " << avg << endl;
                } else {
                    cout << "Course not found.\n";
                }
                break;
            }
            case 7: {
                Course* courses = instructor.get_courses();
                int count = instructor.get_courses_count();
                cout << "Courses taught by " << instructor.get_username() << ":\n";
                for (int i = 0; i < count; i++) {
                    cout << (i + 1) << ". " << courses[i].get_name()
                         << " (Code: " << courses[i].get_code() << ")\n";
                }
                break;
            }
            case 0:
                cout << "Logging out...\n";
                return;
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
}

void show_administrator_main_menu(Administrator &admin,Student* student_list, int& student_count, Instructor* instructor_list, int &instructor_count) {
        int choice = 0;
        while (choice != 7) {
            cout << "\n=== Administrator Menu ===\n";
            cout << "1. Add a new user (student/instructor)\n";
            cout << "2. Remove a user\n";
            cout << "3. Add a new course\n";
            cout << "4. Remove a course\n";
            cout << "5. View all students\n";
            cout << "6. View all instructors\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    int user_type;
                    cout << "\n=== Add User ===\n";
                    cout << "1. Add Student\n";
                    cout << "2. Add Instructor\n";
                    cout << "Enter choice: ";
                    cin >> user_type;

                    while (user_type != 1 && user_type != 2) {
                        cout << "Invalid choice. Please try again.\n";
                        cin>>user_type;
                    }
                    int id;
                    string username, password;

                    cout << "Enter user ID: ";
                    cin >> id;
                    cout << "Enter username: ";
                    cin >> username;
                    cout << "Enter password: ";
                    cin >> password;

                    if (user_type == 1) {
                        admin.add_student(id, username, password, student_list, student_count);
                    } else if (user_type == 2) {
                        admin.add_instructor(id, username, password, instructor_list, instructor_count);
                    } else {
                        cout << "Invalid choice\n";
                    }
                    break;
                }
                case 2: {
                    int user_type;
                    cout << "\n=== Remove User ===\n";
                    cout << "1. Remove Student\n";
                    cout << "2. Remove Instructor\n";
                    cout << "Enter choice: ";
                    cin >> user_type;

                    int id;
                    cout << "Enter user ID to remove: ";
                    cin >> id;

                    if (user_type == 1) {
                        admin.remove_student(student_list, student_count, id);
                    } else if (user_type == 2) {
                        admin.remove_instructor(instructor_list, instructor_count, id);
                    } else {
                        cout << "Invalid choice\n";
                    }
                    break;
                }
                case 3: {
                    string name;
                    int code, credits, num_instructors = 0;

                    cout << "\n=== Add Course ===\n";
                    cout << "Enter course name: ";
                    cin >> name;
                    cout << "Enter course code: ";
                    cin >> code;
                    cout << "Enter credits: ";
                    cin >> credits;

                    cout << "Enter number of instructors (0-3): ";
                    cin >> num_instructors;
                    if (num_instructors > 3) num_instructors = 3; // Maximum 3 instructors per course

                    int* instructor_ids = new int[num_instructors];
                    for (int i = 0; i < num_instructors; i++) {
                        cout << "Enter instructor ID " << (i+1) << ": ";
                        cin >> instructor_ids[i];
                    }

                    admin.add_course(name, code, credits, instructor_ids, num_instructors, instructor_list, instructor_count);
                    break;
                }
                case 4: {
                    int code;
                    cout << "\n=== Remove Course ===\n";
                    cout << "Enter course code to remove: ";
                    cin >> code;
                    admin.remove_course(code);
                    break;
                }
                case 5:
                    admin.view_students(student_list, student_count);
                    break;
                case 6:
                    admin.view_instructors(instructor_list, instructor_count);
                    break;
                case 0:
                    cout << "Exiting administrator menu.\n";
                    return;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        }
    }


void sign_in(User** all_users,Administrator& admin, int& users_count, Student* student_list, int& student_count,
             Instructor* instructor_list, int& instructor_count, Course* course_list, int& course_count) {

    cout << "\n==========================" << endl;
    cout << "         SIGN IN           " << endl;
    cout << "==========================" << endl;

    string username, password;
    bool found = false;
    int index = -1;

    cout << "Username: ";
    cin >> username;

    if (username=="save") {
        ofstream file("students.txt", ios::trunc);
        ofstream file1("courses.txt", ios::trunc);
        ofstream file2("instructors.txt", ios::trunc);

        for (int i = 0; i < course_count; ++i) {
            course_list[i].save_courses("courses.txt");
        }
        for (int i = 0; i < student_count; ++i) {
            student_list[i].save_students("students.txt");
        }
        for (int i = 0; i < instructor_count; ++i) {
            instructor_list[i].save();
        }
        exit(0);
    }
    for (int i = 0; i < users_count; ++i) {
        if (all_users[i]->get_username() == username||username=="admin") {
            found = true;
            index = i;
            break;
        }
    }

    if (!found) {
        cout << "\n Username '" << username << "' not found.\n" << endl;
        return;
    }

    cout << "Password: ";
    cin >> password;
    if (username=="admin" && password=="123") {
        show_administrator_main_menu(admin,
                                     student_list, student_count, instructor_list, instructor_count);
        return;
    }

    if (all_users[index]->get_password() != password ) {
        cout << "\n Incorrect password. Access denied.\n" << endl;
        return;
    }

    cout << "\n Welcome, " << username << "!\n" << endl;

    if (all_users[index]->get_user_type() == "student") {
        show_student_main_menu(static_cast<Student&>(*all_users[index]), course_list, course_count);
    }
    else if (all_users[index]->get_user_type() == "instructor") {
        show_instructor_main_menu(static_cast<Instructor&>(*all_users[index]),
                                  course_list, course_count, student_list, student_count);
    }

    cout << "\n==========================\n" << endl;
}

int extractCourseData(const string& filePath, Course courses[], int maxCourses) {
    ifstream file(filePath);
    string line;
    int count = 0;

    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return count;
    }

    while (count < maxCourses && getline(file, line)) {
        istringstream iss(line);
        int code,credits,num_instructors;
        string name;
        iss >> code >> name >> credits >> num_instructors   ;

        int ins_ids[num_instructors];
        for (int i = 0; i < num_instructors; i++) {
            iss >> ins_ids[i];

        }
        courses[count]=Course(name,code,credits,ins_ids,num_instructors);

        count++;
    }

    file.close();
    return count;
}

int extractStudentData(const string& filePath, Student students[], int maxStudents,Course courses[],int courses_count) {
    ifstream file(filePath);
    string line;
    int count = 0;

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return count;
    }

    while (count < maxStudents && getline(file, line)) {
        istringstream iss(line);
        int id, course_count;
        string name, password;
        iss >> id >> name >> password >> course_count;

        int course_codes[course_count];
        int grades[course_count];
        for (int i = 0; i < course_count; i++) {
            iss >> course_codes[i];
            iss >> grades[i];
        }
        Course* new_courses[course_count];
        for (int i = 0; i < course_count; i++) {
                   new_courses[i]=find_course_by_code(courses,courses_count,course_codes[i]);
                }
        students[count] = Student(id, name, password);
        for (int i = 0; i < course_count; i++) {
            students[count].add(*new_courses[i],grades[i]);
        }

        count++;
    }

    file.close();
    return count;
}
int extractInstructorData(const string& filePath, Instructor instructors[], int maxInstructors,Course courses[],int courses_count) {
    ifstream file(filePath);
    string line;
    int count = 0;

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return count;
    }

    while (count < maxInstructors && getline(file, line)) {
        istringstream iss(line);
        int id, course_count;
        string name, password;
        iss >> id >> name >> password >> course_count;

        int course_codes[course_count];
        for (int i = 0; i < course_count; i++) {
            iss >> course_codes[i];
        }
        Course* new_courses[course_count];
        for (int i = 0; i < course_count; i++) {
            new_courses[i]=find_course_by_code(courses,courses_count,course_codes[i]);
        }
        instructors[count]=Instructor(id,name,password,*new_courses,course_count);
        for (int i = 0; i < course_count; i++) {
            new_courses[i]->add_instructor(id);
        }
        count++;
    }

    file.close();
    return count;
}



int main() {
    Course course_list[10];
    Student student_list[10];
    Instructor instructor_list[10];
    int courses_count=extractCourseData("courses.txt",course_list,10);
    int students_count=extractStudentData("students.txt",student_list,10,course_list,courses_count);
    int instructors_count=extractInstructorData("instructors.txt",instructor_list,10,course_list,courses_count);
    int inital_student_count=students_count;
    int inital_instructor_count=instructors_count;
    Administrator administrator(1,"admin","123");


    User* all_users [100] ;
    for (int i = 0; i < students_count; i++) {
        all_users[i]=&student_list[i];
    }
    for (int i = 0; i < instructors_count; i++) {
        all_users[i]=&instructor_list[i];
    }
    int all_user_count =students_count+instructors_count;

    while (true) {
        sign_in(all_users,administrator,all_user_count,student_list,students_count,instructor_list,instructors_count, course_list,courses_count);
        courses_count=administrator.get_course_count();
        for (int i = 0; i < courses_count; ++i) {
            course_list[i]=administrator.get_course_list()[i];
        }
        if (inital_instructor_count+1==instructors_count) {
            all_users[all_user_count]=&instructor_list[instructors_count-1];
            all_user_count++;
            inital_instructor_count++;
        } else if (inital_student_count+1==students_count){
            all_users[all_user_count]=&student_list[students_count-1];
            all_user_count++;
        }
    }
    return 0;
}
