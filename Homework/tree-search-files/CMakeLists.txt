cmake_minimum_required(VERSION 3.14)
project(tree_search_files)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(tree_search_files
        driver.cpp
        tree_search_1.h)
