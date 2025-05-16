# Student Management System

## Team Members
- **Project Leader:** Saif Eldeen (ID: TBD)
- **Administrator Module Developer:** Youssef Ahmed (ID: 24-101152)
- **Student Module Developer:** Youssef Tharwat (ID: 24-101128)
- **Instructor Module Developer:** Karim Wael (ID: 24-101546)

## Overview
The Student Management System is a comprehensive software solution designed to facilitate the management of educational institutions. This system provides a user-friendly interface for administrators, instructors, and students to perform their respective roles efficiently. The system ensures secure access through role-based authentication and offers a wide range of features tailored to each user type.

## How to Run the Program
1. Ensure you have a C++ compiler installed on your system
2. Compile the program using the provided makefile or your preferred build system
3. Run the executable file generated after compilation
4. The system will start with a login interface where you can enter your credentials

## User Manual

### Login
- Launch the program
- Enter your username and password
- Select your role (Administrator/Instructor/Student)
- Click login to access the system

### Administrator Access
1. **Managing Users**
   - Add new instructors or students
   - Remove existing users
   - View all registered users

2. **Managing Courses**
   - Add new courses to the system
   - Remove existing courses
   - Assign instructors to courses

### Instructor Access
1. **Course Management**
   - View assigned courses (up to 5 courses)
   - Add/remove courses from teaching list
   - Upload course materials

2. **Grade Management**
   - Enter and update student grades
   - View grade statistics (max, min, average)
   - Generate grade reports

### Student Access
1. **Course Registration**
   - View available courses
   - Enroll in courses (up to 6 courses)
   - Drop courses

2. **Academic Information**
   - View grades for enrolled courses
   - Calculate average grade
   - Access course materials

## Key Features

This system includes the following core functionalities:

* **User Authentication:** Secure login for all users (administrators, instructors, and students) using username and password.
* **Administrator Privileges:**
    * Add new users (instructors or students) to the system.
    * Remove existing users from the system.
    * Add new courses to the system.
    * Remove existing courses from the system.
* **Instructor Capabilities:**
    * Manage their teaching list:
        * Add a new course to their list (up to 5 courses).
        * Remove a course from their list.
    * Manage course materials (implementation details of material management are to be determined).
    * Update student grades for the courses they teach.
    * Perform basic statistics on a specific course they teach:
        * Calculate the maximum grade.
        * Calculate the minimum grade.
        * Calculate the average grade.
* **Student Capabilities:**
    * Enroll in available courses (up to 6 courses).
    * Access course materials (implementation details of material access are to be determined).
    * Drop a course from their enrolled courses.
    * View their grade in specific enrolled courses.
    * Calculate their average grade across all registered courses.

## Implementation Guide

The system is implemented using object-oriented principles with the following classes and their attributes:

### User
* `user_id`: Unique identifier for the user.
* `username`: Username for login.
* `password`: Password for login.

### Administrator 
* No additional attributes.
* **Initial Administrator:** The system starts with at least one pre-defined administrator account (username and password will be specified in the initial setup).
* **Functions:**
    * `add_user`: Adds a new user (instructor or student) to the system. `user_details` will contain necessary information like ID, name, etc.
    * `remove_user`: Removes a user from the system based on their ID.
    * `add_course`: Adds a new course to the system. `course_details` will include name, code, instructor IDs, and credits.
    * `remove_course`: Removes a course from the system based on its code.

### Instructor 
* `instructor_id`: Unique identifier for the instructor.
* `name`: Name of the instructor.
* `courses_taught`: A list to store the IDs of the courses taught by the instructor (maximum 5).
* **Functions:**
    * `add_course_to_teaching_list`: Adds a course to the instructor's teaching list.
    * `remove_course_from_teaching_list`: Removes a course from the instructor's teaching list.
    * `add_update_grade`: Adds or updates the grade of a specific student in a specific course taught by the instructor. This update should be reflected in the student's record.
    * `get_max_grade`: Returns the maximum grade achieved in a specific course taught by the instructor.
    * `get_min_grade`: Returns the minimum grade achieved in a specific course taught by the instructor.
    * `get_average_grade`: Returns the average grade in a specific course taught by the instructor.
    * `add_material`: Adds material to a specific course (implementation details of how materials are stored are flexible).
    * `remove_material`: Removes material from a specific course (implementation details of material identification are flexible).

### Student
* `student_id`: Unique identifier for the student.
* `name`: Name of the student.
* `registered_courses`: A dictionary or list of tuples to store the IDs of the courses the student is enrolled in and their corresponding grades (e.g., `{course_id: grade}`). Maximum 6 courses.
* **Functions:**
    * `enroll_in_course`: Enrolls the student in a new course.
    * `drop_course`: Drops a course from the student's enrolled courses.
    * `view_grade`: Returns the student's grade in a specific enrolled course.
    * `get_average_grade`: Calculates and returns the student's average grade across all registered courses.
    * `access_material`: Allows the student to access materials for a specific course (implementation details of material access are flexible).

