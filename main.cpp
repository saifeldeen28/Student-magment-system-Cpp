#include <iostream>
#include <fstream>
#include <sstream>

#include "admin.h"
#include "User.h"
#include "Course.h"
#include "instructor.h"
#include "student.h"
using namespace std;

// Function prototypes
Course* find_course_by_code(Course* course_list, int course_count, int code);
Student* find_student_by_id(Student* student_list, int student_count, int id);
void show_student_main_menu(Student &student, Course* course_list, int &course_count);
void show_instructor_main_menu(Instructor &instructor, Course* course_list, int &course_count, Student* student_list, int &student_count);
void show_administrator_main_menu(Administrator &admin, Student* student_list, int& student_count, Instructor* instructor_list, int &instructor_count, Course* course_list, int& course_count);
void sign_in(User** all_users, Administrator& admin, int& users_count, Student* student_list, int& student_count, Instructor* instructor_list, int& instructor_count, Course* course_list, int& course_count,int sign_in_count);
int extractCourseData(const string& filePath, Course courses[], int maxCourses);
int extractStudentData(const string& filePath, Student students[], int maxStudents, Course courses[], int courses_count);
int extractInstructorData(const string& filePath, Instructor instructors[], int maxInstructors, Course courses[], int courses_count);

// Helper function to check if a course belongs to an instructor
bool is_instructor_course(const Instructor& instructor, const Course& course) {
    Course* instructor_courses = instructor.get_courses();
    int course_count = instructor.get_courses_count();
    
    for (int i = 0; i < course_count; i++) {
        if (instructor_courses[i].get_code() == course.get_code()) {
            return true;
        }
    }
    return false;
}

int main() {
    Course course_list[10];
    Student student_list[10];
    Instructor instructor_list[10];
    int courses_count=extractCourseData("courses.txt",course_list,10);
    int students_count=extractStudentData("students.txt",student_list,10,course_list,courses_count);
    int instructors_count=extractInstructorData("instructors.txt",instructor_list,10,course_list,courses_count);
    int initial_student_count=students_count;
    int initial_instructor_count=instructors_count;
    Administrator administrator(1,"admin","123",course_list,courses_count);


    User* all_users [100];
    all_users[0] = &administrator;

    for (int i = 0; i < students_count; i++) {
        all_users[i+1] = &student_list[i];
    }
    for (int i = 0; i < instructors_count; i++) {
        all_users[i+students_count+1] = &instructor_list[i];
    }

    int all_user_count = 1 + students_count + instructors_count;

    // Display welcome message
    cout << "\n";
    cout << "+------------------------------------------------------+\n";
    cout << "|                                                      |\n";
    cout << "|       WELCOME TO STUDENT MANAGEMENT SYSTEM           |\n";
    cout << "|                                                      |\n";
    cout << "+------------------------------------------------------+\n\n";

    int sign_in_count = 0;  // Moved outside the loop
    while (true) {
        sign_in(all_users,administrator,all_user_count,student_list,students_count,instructor_list,instructors_count, course_list,courses_count,sign_in_count);
        sign_in_count++;  // Increment the counter


        all_users[0] = &administrator;

        // Add any new instructors
        while (initial_instructor_count < instructors_count) {
            all_users[all_user_count] = &instructor_list[initial_instructor_count];
            all_user_count++;
            initial_instructor_count++;
        }

        // Add any new students
        while (initial_student_count < students_count) {
            all_users[all_user_count] = &student_list[initial_student_count];
            all_user_count++;
            initial_student_count++;
        }
    }

    return 0;
}

void sign_in(User** all_users,Administrator& admin, int& users_count, Student* student_list, int& student_count,
             Instructor* instructor_list, int& instructor_count, Course* course_list, int& course_count,int sign_in_count) {

    if (sign_in_count!=0) {
        int choice;
        cout << "\n+-------------------+\n";
        cout << "| SAVE OPTIONS      |\n";
        cout << "+-------------------+\n";
        cout << "1. Save and exit\n";
        cout << "2. Continue \n";
        cout << "Enter your choice (1-2): ";
        cin >> choice;

        if (choice == 1) {
            cout << "Saving all data and exiting...\n";
            // Clear files first
            ofstream file("students.txt", ios::trunc);
            file.close();
            ofstream file1("courses.txt", ios::trunc);
            file1.close();
            ofstream file2("instructors.txt", ios::trunc);
            file2.close();

            // First save courses since they don't inherit from User
            for (int i = 0; i < course_count; ++i) {
                course_list[i].save();
            }

            // Then save all users using polymorphism
            for (int i = 1; i < users_count; ++i) {// Skip admin since it doesn't need saving
                    all_users[i]->save();
            }

            cout << "\n+--------------------------------------------------+\n";
            cout << "|                 Session Ended                    |\n";
            cout << "+--------------------------------------------------+\n\n";

            exit(0);
        }
    }

    cout <<
    "   _____ _               _____       \n"
    "  / ____(_)             |_   _|      \n"
    " | (___  _  __ _ _ __     | |  _ __  \n"
    "  \\___ \\| |/ _` | '_ \\    | | | '_ \\ \n"
    "  ____) | | (_| | | | |  _| |_| | | |\n"
    " |_____/|_|\\__, |_| |_| |_____|_| |_|\n"
    "            __/ |                    \n"
    "           |___/                     \n";

    string username, password;
    bool found = false;
    int index = -1;

    cout << "Username: ";
    cin >> username;

    for (int i = 0; i < users_count; ++i) {
        if (all_users[i]->get_username() == username) {
            found = true;
            index = i;
            break;
        }
    }

    if (!found) {
        cout << "\n+-------------------------+\n";
        cout << "| Error: User not found! |\n";
        cout << "+-------------------------+\n\n";
        return;
    }

    cout << "Password: ";
    cin >> password;

    if (all_users[index]->get_password() != password ) {
        cout << "\n+---------------------------+\n";
        cout << "| Error: Invalid password! |\n";
        cout << "+---------------------------+\n\n";
        return;
    }

    cout << "\n+--------------------------------+\n";
    cout << "| Welcome, " << username;
    for (unsigned i = username.length(); i < 22; i++) cout << " ";
    cout << "|\n";
    cout << "+--------------------------------+\n\n";

    if (all_users[index]->get_username() == "admin") {

        show_administrator_main_menu(admin, student_list, student_count, instructor_list, instructor_count, course_list, course_count);
        course_count=admin.get_course_count();
        course_list=admin.get_course_list();
    }
    else if (all_users[index]->get_user_type() == "student") {
        show_student_main_menu(static_cast<Student&>(*all_users[index]), course_list, course_count);
    }
    else if (all_users[index]->get_user_type() == "instructor") {
        show_instructor_main_menu(static_cast<Instructor&>(*all_users[index]),
                                  course_list, course_count, student_list, student_count);
    }
}

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
    int choice = -1;  // Initialize to -1 to enter the loop
    while (choice != 0) {  // Only exit when user chooses 0
        cout << "\n+-------------------------------+\n";
        cout << "|        STUDENT MENU           |\n";
        cout << "+-------------------------------+\n";
        cout << "| 1. Register in a new course   |\n";
        cout << "| 2. Drop a course              |\n";
        cout << "| 3. View grade in a course     |\n";
        cout << "| 4. View average grade         |\n";
        cout << "| 5. View registered courses    |\n";
        cout << "| 6. View performance report    |\n";
        cout << "| 0. Log out                    |\n";
        cout << "+-------------------------------+\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int course_code;
                cout << "\n+----------------------------+\n";
                cout << "|   REGISTER FOR COURSE      |\n";
                cout << "+----------------------------+\n";
                cout << "Enter course code to register: ";
                cin >> course_code;

                Course* course_to_add = find_course_by_code(course_list, course_count, course_code);
                if (course_to_add!=nullptr) {
                    cout << "Your student ID is: " << student.get_id() << endl;
                    student.add(*course_to_add);
                    course_to_add->add_student(student.get_id());
                } else {
                    cout << "\n+---------------------------+\n";
                    cout << "| Error: Course not found!  |\n";
                    cout << "+---------------------------+\n";
                }
                break;
            }
            case 2: {
                int course_code;
                cout << "\n+----------------------------+\n";
                cout << "|     DROP COURSE            |\n";
                cout << "+----------------------------+\n";
                cout << "Enter course code to drop: ";
                cin >> course_code;

                Course* course_to_drop = find_course_by_code(course_list, course_count, course_code);
                if (course_to_drop) {
                    student.drop(*course_to_drop);
                } else {
                    cout << "\n+----------------------------------------+\n";
                    cout << "| Error: Course not found or not registered! |\n";
                    cout << "+----------------------------------------+\n";
                }
                break;
            }
            case 3: {
                int course_code;
                cout << "\n+----------------------------+\n";
                cout << "|     VIEW COURSE GRADE      |\n";
                cout << "+----------------------------+\n";
                cout << "Enter course code to view grade: ";
                cin >> course_code;

                Course* course = find_course_by_code(course_list, course_count, course_code);
                if (course) {
                    int grade = course->get_grade(student.get_id());
                    if (grade != -1) {
                        cout << "\n+-----------------------------------+\n";
                        cout << "| Your grade in " << course->get_name() << ": " << grade << endl;
                        cout << "+-----------------------------------+\n";
                    } else {
                        cout << "\n+----------------------------------------+\n";
                        cout << "| You are not registered in this course! |\n";
                        cout << "+----------------------------------------+\n";
                    }
                } else {
                    cout << "\n+---------------------------+\n";
                    cout << "| Error: Course not found!  |\n";
                    cout << "+---------------------------+\n";
                }
                break;
            }
            case 4: {
                cout << "\n+----------------------------+\n";
                cout << "|    VIEW AVERAGE GRADE      |\n";
                cout << "+----------------------------+\n";
                student.average_grade();
                break;
            }
            case 5: {
                cout << "\n+----------------------------+\n";
                cout << "|   VIEW REGISTERED COURSES  |\n";
                cout << "+----------------------------+\n";
                student.view_grades();
                break;
            }
            case 6: {
                student.Card();  // Show student performance report
                break;
            }
            case 0: {
                cout << "\n+-------------------+\n";
                cout << "|   Logging out...  |\n";
                cout << "+-------------------+\n";
                return;
            }
            default:
                cout << "\n+---------------------------+\n";
                cout << "| Error: Invalid selection! |\n";
                cout << "+---------------------------+\n";
                break;
        }
    }
}

void show_instructor_main_menu(Instructor &instructor, Course* course_list, int &course_count, Student* student_list, int &student_count) {
    int choice = -1;  // Initialize to -1 to enter the loop
    while (choice != 0) {  // Only exit when user chooses 0
        cout << "\n+-----------------------------------+\n";
        cout << "|          INSTRUCTOR MENU          |\n";
        cout << "+-----------------------------------+\n";
        cout << "| 1. Add course to teaching list    |\n";
        cout << "| 2. Remove course from teaching    |\n";
        cout << "| 3. Add/update student grades      |\n";
        cout << "| 4. View max grade in a course     |\n";
        cout << "| 5. View min grade in a course     |\n";
        cout << "| 6. View average grade in course   |\n";
        cout << "| 7. View list of courses taught    |\n";
        cout << "| 8. View instructor performance    |\n";
        cout << "| 9. View course performance        |\n";
        cout << "| 0. Log out                        |\n";
        cout << "+-----------------------------------+\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int course_code;
                cout << "\n+-------------------------------+\n";
                cout << "|     ADD COURSE TO TEACHING    |\n";
                cout << "+-------------------------------+\n";
                cout << "Enter course code to add: ";
                cin >> course_code;

                Course* course = find_course_by_code(course_list, course_count, course_code);
                if (course!=nullptr) {
                    course->add_instructor(instructor.get_id());
                    instructor.add_course(*course);
                } else {
                    cout << "\n+---------------------------+\n";
                    cout << "| Error: Course not found!  |\n";
                    cout << "+---------------------------+\n";
                }
                break;
            }
            case 2: {
                int course_code;
                cout << "\n+--------------------------------+\n";
                cout << "|     REMOVE COURSE FROM LIST    |\n";
                cout << "+--------------------------------+\n";
                cout << "Enter course code to remove: ";
                cin >> course_code;

                Course* course = find_course_by_code(course_list, course_count, course_code);
                if (course && is_instructor_course(instructor, *course)) {
                    instructor.remove_course(*course);
                } else {
                    cout << "\n+----------------------------------------+\n";
                    cout << "| Error: Course not found or not teaching! |\n";
                    cout << "+----------------------------------------+\n";
                }
                break;
            }
            case 3: {
                int course_code, student_id, grade;
                cout << "\n+-------------------------------+\n";
                cout << "|     UPDATE STUDENT GRADES     |\n";
                cout << "+-------------------------------+\n";
                cout << "Enter course code: ";
                cin >> course_code;
                Course* course = find_course_by_code(course_list, course_count, course_code);
                if (!course) {
                    cout << "\n+---------------------------+\n";
                    cout << "| Error: Course not found!  |\n";
                    cout << "+---------------------------+\n";
                    break;
                }

                if (!is_instructor_course(instructor, *course)) {
                    cout << "\n+----------------------------------------+\n";
                    cout << "| Error: You don't teach this course!    |\n";
                    cout << "+----------------------------------------+\n";
                    break;
                }

                // Display registered students in this course
                if (course->get_number_of_students() == 0) {
                    cout << "\n+----------------------------------------+\n";
                    cout << "| No students registered for this course!|\n";
                    cout << "+----------------------------------------+\n";
                    break;
                }

                cout << "\n+-------------------------------+\n";
                cout << "| STUDENTS IN THIS COURSE       |\n";
                cout << "+-------------------------------+\n";
                for (int i = 0; i < course->get_number_of_students(); i++) {
                    int stu_id = course->get_student_ids()[i];
                    Student* stu = find_student_by_id(student_list, student_count, stu_id);
                    if (stu) {
                        cout << "| ID: " << stu_id << ", Username: " << stu->get_username() << endl;
                    } else {
                        cout << "| ID: " << stu_id << " (unknown username)" << endl;
                    }
                }
                cout << "+-------------------------------+\n";

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
                    cout << "\n+----------------------------------------+\n";
                    cout << "| Student not registered for this course! |\n";
                    cout << "+----------------------------------------+\n";
                    break;
                }
                cout << "Enter new grade: ";
                cin >> grade;

                // Validate grade
                if (grade < 0 || grade > 100) {
                    cout << "\n+----------------------------------------+\n";
                    cout << "| Invalid grade! Must be between 0-100.   |\n";
                    cout << "+----------------------------------------+\n";
                    break;
                }

                Student* student = find_student_by_id(student_list, student_count, student_id);
                if (student) {
                    instructor.set_grade(*course, *student, grade);
                    cout << "\n+-------------------------------+\n";
                    cout << "| Grade updated successfully!   |\n";
                    cout << "+-------------------------------+\n";
                } else {
                    cout << "\n+---------------------------+\n";
                    cout << "| Error: Student not found! |\n";
                    cout << "+---------------------------+\n";
                }
                break;
            }
            case 4: {
                int course_code;
                cout << "\n+-------------------------------+\n";
                cout << "|     VIEW MAXIMUM GRADE        |\n";
                cout << "+-------------------------------+\n";
                cout << "Enter course code: ";
                cin >> course_code;

                Course* course = find_course_by_code(course_list, course_count, course_code);
                if (course && is_instructor_course(instructor, *course)) {
                    double max = instructor.max_grade(*course);
                    cout << "\n+-------------------------------+\n";
                    cout << "| Maximum grade in course: " << max << endl;
                    cout << "+-------------------------------+\n";
                } else {
                    cout << "\n+----------------------------------------+\n";
                    cout << "| Error: Course not found or not teaching! |\n";
                    cout << "+----------------------------------------+\n";
                }
                break;
            }
            case 5: {
                int course_code;
                cout << "\n+-------------------------------+\n";
                cout << "|     VIEW MINIMUM GRADE        |\n";
                cout << "+-------------------------------+\n";
                cout << "Enter course code: ";
                cin >> course_code;

                Course* course = find_course_by_code(course_list, course_count, course_code);
                if (course && is_instructor_course(instructor, *course)) {
                    double min = instructor.min_grade(*course);
                    cout << "\n+-------------------------------+\n";
                    cout << "| Minimum grade in course: " << min << endl;
                    cout << "+-------------------------------+\n";
                } else {
                    cout << "\n+----------------------------------------+\n";
                    cout << "| Error: Course not found or not teaching! |\n";
                    cout << "+----------------------------------------+\n";
                }
                break;
            }
            case 6: {
                int course_code;
                cout << "\n+-------------------------------+\n";
                cout << "|     VIEW AVERAGE GRADE        |\n";
                cout << "+-------------------------------+\n";
                cout << "Enter course code: ";
                cin >> course_code;

                Course* course = find_course_by_code(course_list, course_count, course_code);
                if (course && is_instructor_course(instructor, *course)) {
                    double avg = instructor.avg_grade(*course);
                    cout << "\n+-------------------------------+\n";
                    cout << "| Average grade in course: " << avg << endl;
                    cout << "+-------------------------------+\n";
                } else {
                    cout << "\n+----------------------------------------+\n";
                    cout << "| Error: Course not found or not teaching! |\n";
                    cout << "+----------------------------------------+\n";
                }
                break;
            }
            case 7: {
                Course* courses = instructor.get_courses();
                int count = instructor.get_courses_count();
                cout << "\n+-------------------------------+\n";
                cout << "| COURSES TAUGHT BY " << instructor.get_username();
                for (unsigned i = instructor.get_username().length(); i < 12; i++) cout << " ";
                cout << "|\n";
                cout << "+-------------------------------+\n";

                if (count == 0) {
                    cout << "| No courses currently taught    |\n";
                    cout << "+-------------------------------+\n";
                } else {
                    for (int i = 0; i < count; i++) {
                        cout << "| " << (i + 1) << ". " << courses[i].get_name()
                             << " (Code: " << courses[i].get_code() << ")" << endl;
                    }
                    cout << "+-------------------------------+\n";
                }
                break;
            }
            case 8: {
                instructor.performance_I();
                break;
            }
            case 9: {
                int course_code;
                cout << "\n+-------------------------------+\n";
                cout << "|     VIEW COURSE PERFORMANCE   |\n";
                cout << "+-------------------------------+\n";
                cout << "Enter course code: ";
                cin >> course_code;

                Course* course = find_course_by_code(course_list, course_count, course_code);
                if (course && is_instructor_course(instructor, *course)) {
                    course->performance_C();
                } else {
                    cout << "\n+----------------------------------------+\n";
                    cout << "| Error: Course not found or not teaching! |\n";
                    cout << "+----------------------------------------+\n";
                }
                break;
            }
            case 0: {
                cout << "\n+-------------------+\n";
                cout << "|   Logging out...  |\n";
                cout << "+-------------------+\n";
                return;
            }
            default:
                cout << "\n+---------------------------+\n";
                cout << "| Error: Invalid selection! |\n";
                cout << "+---------------------------+\n";
                break;
        }
    }
}

void show_administrator_main_menu(Administrator &admin, Student* student_list, int& student_count, Instructor* instructor_list, int &instructor_count, Course* course_list, int& course_count) {
    admin.set_course_count(course_count);
    admin.set_course_list(course_list);
        int choice = 0;
        while (choice != 8) {
            cout << "\n+-----------------------------------+\n";
            cout << "|        ADMINISTRATOR MENU         |\n";
            cout << "+-----------------------------------+\n";
            cout << "| 1. Add a new user                 |\n";
            cout << "| 2. Remove a user                  |\n";
            cout << "| 3. Add a new course               |\n";
            cout << "| 4. Remove a course                |\n";
            cout << "| 5. View all students              |\n";
            cout << "| 6. View all instructors           |\n";
            cout << "| 7. View all courses               |\n";
            cout << "| 8. View students by GPA           |\n";
            cout << "| 0. Exit                           |\n";
            cout << "+-----------------------------------+\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    int user_type;
                    cout << "\n+-------------------+\n";
                    cout << "|     ADD USER      |\n";
                    cout << "+-------------------+\n";
                    cout << "| 1. Add Student    |\n";
                    cout << "| 2. Add Instructor |\n";
                    cout << "+-------------------+\n";
                    cout << "Enter choice: ";
                    cin >> user_type;

                    while (user_type != 1 && user_type != 2) {
                        cout << "\n+---------------------------+\n";
                        cout << "| Error: Invalid selection! |\n";
                        cout << "+---------------------------+\n";
                        cout << "Please enter 1 or 2: ";
                        cin>>user_type;
                    }
                    int id;
                    string username, password;

                    cout << "\n+---------------------------+\n";
                    cout << "| Enter user details:       |\n";
                    cout << "+---------------------------+\n";
                    cout << "User ID: ";
                    cin >> id;
                    cout << "Username: ";
                    cin >> username;
                    cout << "Password: ";
                    cin >> password;

                    if (user_type == 1) {
                        admin.add_student(id, username, password, student_list, student_count);
                    } else if (user_type == 2) {
                        admin.add_instructor(id, username, password, instructor_list, instructor_count);
                    } else {
                        cout << "\n+---------------------------+\n";
                        cout << "| Error: Invalid selection! |\n";
                        cout << "+---------------------------+\n";
                    }
                    break;
                }
                case 2: {
                    int user_type;
                    cout << "\n+-------------------+\n";
                    cout << "|    REMOVE USER    |\n";
                    cout << "+-------------------+\n";
                    cout << "| 1. Remove Student |\n";
                    cout << "| 2. Remove Instructor |\n";
                    cout << "+-------------------+\n";
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
                        cout << "\n+---------------------------+\n";
                        cout << "| Error: Invalid selection! |\n";
                        cout << "+---------------------------+\n";
                    }
                    break;
                }
                case 3: {
                    string name;
                    int code, credits, num_instructors = 0;

                    cout << "\n+-------------------+\n";
                    cout << "|    ADD COURSE     |\n";
                    cout << "+-------------------+\n";
                    cout << "Course name: ";
                    cin >> name;
                    cout << "Course code: ";
                    cin >> code;
                    cout << "Credits: ";
                    cin >> credits;


                    int* instructor_ids = new int[num_instructors];

                    admin.add_course(name, code, credits, instructor_ids, num_instructors, instructor_list, instructor_count);
                    break;
                }
                case 4: {
                    int code;
                    cout << "\n+-------------------+\n";
                    cout << "|   REMOVE COURSE   |\n";
                    cout << "+-------------------+\n";
                    cout << "Enter course code to remove: ";
                    cin >> code;
                    admin.remove_course(code, student_list, student_count, instructor_list, instructor_count);
                    break;
                }
                case 5:
                    admin.view_students(student_list, student_count);
                    break;
                case 6:
                    admin.view_instructors(instructor_list, instructor_count);
                    break;
                case 7:
                    admin.view_courses();
                    break;
                case 8:
                    admin.display_students_by_GPA(student_list, student_count);
                    break;
                case 0: {
                    cout << "\n+-----------------------------------+\n";
                    cout << "| Exiting administrator menu.       |\n";
                    cout << "+-----------------------------------+\n";
                    return;
                }
                default:
                    cout << "\n+---------------------------+\n";
                    cout << "| Error: Invalid selection! |\n";
                    cout << "+---------------------------+\n";
                    break;
            }
        }
    }




int extractCourseData(const string& filePath, Course courses[], int maxCourses) {
    ifstream file(filePath);
    string line;
    int count = 0;

    if (!file.is_open()) {
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
