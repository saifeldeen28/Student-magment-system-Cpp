#include <iostream>
#include <vector>

#include "admin.h"
#include "User.h"
#include "Course.h"
#include "instructor.h"
#include "student.h"
using namespace std;
void show_student_main_menu(Student &student) {
    cout<<"student menu "<<student.getUsername()<<endl;
}
void show_instructor_main_menu(Instructor &instructor) {
    cout<<"instructor menu  "<<instructor.getUsername()<<endl;
}
void show_administrator_main_menu(Administrator &admin,Student* student_list, int student_count, Instructor* instructor_list, int instructor_count) {
        int choice = 0;
        while (choice != 5) {
            cout << "\n=== Administrator Menu ===\n";
            cout << "1. Add a new user (student/instructor)\n";
            cout << "2. Remove a user\n";
            cout << "3. Add a new course\n";
            cout << "4. Remove a course\n";
            cout << "5. Exit\n";
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
                    int* grades = new int[num_students];

                    for (int i = 0; i < num_students; i++) {
                        cout << "Enter student ID " << (i+1) << ": ";
                        cin >> student_ids[i];
                        cout << "Enter grade for student " << student_ids[i] << ": ";
                        cin >> grades[i];
                    }

                    cout << "Enter number of instructors (0-3): ";
                    cin >> num_instructors;
                    if (num_instructors > 3) num_instructors = 3; // Maximum 3 instructors per course

                    int* instructor_ids = new int[num_instructors];
                    for (int i = 0; i < num_instructors; i++) {
                        cout << "Enter instructor ID " << (i+1) << ": ";
                        cin >> instructor_ids[i];
                    }

                    admin.add_course(name, code, credits, grades, student_ids, instructor_ids, num_students, num_instructors);

                    delete[] student_ids;
                    delete[] grades;
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
                    cout << "Exiting administrator menu.\n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
            }
        }
    }

bool signIn(User* all_users,int users_count,Student* student_list, int student_count, Instructor* instructor_list, int instructor_count) {
    string username, password;
    bool flag = false;
    int index = -1;
    cout<<"Enter username ";
    cin>>username;

    for (int i = 0; i <= users_count; i++) {
        if (all_users[i].getUsername() == username) {
            flag = true;
            index = i;
            break;
        }
    }
    if (!flag ) {
        cout<<"Username "<<username <<" does not exist.\n";
        return false;
    }
    cout<<"Enter password ";
    cin>>password;
    if (all_users[index].getPassword()!=password || (password != "123"&& username!="admin")) {
        cout<<"Invalid password entered"<<endl;
        return false;
    }
    if (username=="admin" && password=="123") {
        show_administrator_main_menu(static_cast<Administrator &>(all_users[index]),student_list,student_count,instructor_list,instructor_count);
    }
    if (all_users[index].getUserType()=="student") {
        show_student_main_menu(static_cast<Student &>(all_users[index]));
    }
    if (all_users[index].getUserType()=="instructor") {
        show_instructor_main_menu(static_cast<Instructor &>(all_users[index]));
    }
    return true;
}

int main() {
    Student student;
    Instructor instructor;
    Administrator administrator(1,"admin","123");
    Student s1(1,"saif","123");
    Student s2(2,"joe","456");
    Student s3(3,"karim","789");
    Student s4(4,"mostafa","789");
    Student student_list[]={s1,s2,s3,s4};
    int student_ids[2]={1,2};
    int student_grades[2]={90,91};
    int instructor_ids[1]={1};
    Course c1("physics",1,3,student_ids,student_grades,2,instructor_ids,1);
    Course* instructor_courses = {&c1};
    Instructor i1(1,"hassan","123",instructor_courses,1);
    Instructor instructor_list[]={i1};
    User all_users[]={
        s1,
        s2,
        i1,
        administrator
    };
    signIn(all_users,3,student_list,4,instructor_list,1);












    ///test cases
    /*
    Student s1(1,"saif","123");
    Student s2(2,"joe","456");
    Student s3(3,"karim","789");
    Student s4(4,"mostafa","789");
    int student_ids[2]={1,2};
    int student_grades[2]={90,91};
    int instructor_ids[1]={1};
    Course c1("physics",1,3,student_ids,student_grades,2,instructor_ids,1);
    //student and course testing
    c1.add_student(s3.getId(),80);
    c1.print_grades();
    c1.drop_stuent(s1.getId());
    c1.print_grades();
    s4.add(c1,99);
    c1.print_grades();
    s4.viewGrades();
    s4.drop(c1);
    c1.print_grades();
    cout<<endl<<endl;
    //instructor testing
    Course* instructor_courses = {&c1};
    Instructor i1(1,"hassan","123",instructor_courses,1);
    Student s5(5,"adham","123");

    cout<<i1.avg_grade(c1)<<endl;
    cout<<i1.min_grade(c1)<<endl;
    s5.add(c1);
    c1.add_student(s5.getId(),70);
    i1.set_grade(c1,s5,99);
    cout<<i1.max_grade(c1)<<endl;
    s5.viewGrades();
    i1.remove_course(c1);*/



    return 0;
}