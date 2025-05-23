cmake_minimum_required(VERSION 3.31)
project(final_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(final_project main.cpp
        user.h
        Course.h
        admin.h
        instructor.h
)

# Copy text files to build directory
configure_file(${CMAKE_SOURCE_DIR}/courses.txt ${CMAKE_BINARY_DIR}/courses.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/students.txt ${CMAKE_BINARY_DIR}/students.txt COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/instructors.txt ${CMAKE_BINARY_DIR}/instructors.txt COPYONLY)
