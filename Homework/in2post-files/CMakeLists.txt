cmake_minimum_required(VERSION 3.14)
project(in2post_files)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(in2post_files
        driver.cpp
        infix2postfix.h infix2postfix.cpp)
