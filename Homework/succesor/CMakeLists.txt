cmake_minimum_required(VERSION 3.14)
project(succesor)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(succesor
        driver.cpp
        node.cpp
        node.h
        successor.h successor.cpp)
