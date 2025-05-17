#include <iostream>
#include <vector>

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
        cout << "6. Log out\n";
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
            case 6:
                cout << "Logging out...\n";
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
        cout << "8. Log out\n";
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
                cout << "Enter student ID: ";
                cin >> student_id;
                cout << "Enter new grade: ";
                cin >> grade;

                Course* course = find_course_by_code(course_list, course_count, course_code);
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
            case 8:
                cout << "Logging out...\n";
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
            cout << "7. Exit\n";
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
                    int code, credits, num_students = 0, num_instructors = 0;

                    cout << "\n=== Add Course ===\n";
                    cout << "Enter course name: ";
                    cin >> name;
                    cout << "Enter course code: ";
                    cin >> code;
                    cout << "Enter credits: ";
                    cin >> credits;

                    cout << "Enter number of students (0 for none): ";
                    cin >> num_students;

                    int* student_ids = new int[num_students];

                    for (int i = 0; i < num_students; i++) {
                        cout << "Enter student ID " << (i+1) << ": ";
                        cin >> student_ids[i];
                    }

                    cout << "Enter number of instructors (0-3): ";
                    cin >> num_instructors;
                    if (num_instructors > 3) num_instructors = 3; // Maximum 3 instructors per course

                    int* instructor_ids = new int[num_instructors];
                    for (int i = 0; i < num_instructors; i++) {
                        cout << "Enter instructor ID " << (i+1) << ": ";
                        cin >> instructor_ids[i];
                    }

                    admin.add_course(name, code, credits, student_ids, instructor_ids, num_instructors, instructor_list, instructor_count);

                    delete[] student_ids;
                    delete[] instructor_ids;
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
                case 7:
                    cout << "Exiting administrator menu.\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        }
    }


void sign_in(User** all_users, int &users_count, Student* student_list, int &student_count,
            Instructor* instructor_list, int &instructor_count, Course* course_list, int& course_count) {
    string username, password;
    bool flag = false;
    int index = -1;
    cout<<"Enter username ";
    cin>>username;

    for (int i = 0; i < users_count; i++) {
        if (all_users[i]->get_username() == username) {
            flag = true;
            index = i;
            break;
        }
    }
    if (!flag ) {
        cout<<"Username "<<username <<" does not exist.\n";
        return ;
    }
    cout<<"Enter password ";
    cin>>password;
    if (all_users[index]->get_password()!=password && username!="admin" ) {
        cout<<"Invalid password entered"<<endl;
        return ;
    }
    if (username=="admin" && password=="123") {
        show_administrator_main_menu(static_cast<Administrator &>(*all_users[index]),student_list,student_count,instructor_list,instructor_count);
    }
    else if (all_users[index]->get_user_type()=="student") {
        show_student_main_menu(static_cast<Student &>(*all_users[index]), course_list, course_count);
    }
    else if (all_users[index]->get_user_type()=="instructor") {
        show_instructor_main_menu(static_cast<Instructor &>(*all_users[index]), course_list, course_count, student_list, student_count);
    }
}

int main() {
    Administrator administrator(1,"admin","123");

    int initial_student_count = 4;
    Student* student_list = new Student[initial_student_count];
    student_list[0] = Student(1,"saif","123");
    student_list[1] = Student(2,"joe","456");
    student_list[2] = Student(3,"karim","789");
    student_list[3] = Student(4,"mostafa","789");
    int student_count = initial_student_count;

    // Create course
    int student_ids[4]={1,2,3,4};
    int student_grades[4]={90,91,45,65};
    int instructor_ids[1]={1};
    Course c1("physics",1,3,student_ids,student_grades,2,instructor_ids,1);
    Course c2("math",2,4,student_ids,student_grades,2,instructor_ids,1);
    /*student_list[0].add(c1);
    student_list[1].add(c1);*/

    int initial_instructor_count = 1;
    Course* instructor_courses[1] = {&c1};
    Instructor i1(1,"hassan","123",*instructor_courses,1);
    Instructor* instructor_list=new Instructor[initial_instructor_count]{i1};
    int instructor_count = initial_instructor_count;
    Course* course_list = new Course[2]{
    c1,c2};

    User** all_users = new User*[6] {
        &student_list[0],
        &student_list[1],
        &student_list[2],
        &student_list[3],
        &instructor_list[0],
        &administrator
    };
    int all_user_count =6;
    int course_count=2;
    while (true) {
        sign_in(all_users,all_user_count,student_list,student_count,instructor_list,instructor_count, course_list,course_count);
    }

    delete[] student_list;
    delete[] instructor_list;
    delete[] all_users;

    return 1;
}