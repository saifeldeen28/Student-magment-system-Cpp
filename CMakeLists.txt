cmake_minimum_required(VERSION 3.31)
project(final_project)

set(CMAKE_CXX_STANDARD 20)

add_executable(final_project main.cpp
        user.h
        Course.h
        admin.h
        instructor.h)
