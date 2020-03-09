cmake_minimum_required(VERSION 3.14)
project(Assignment3)

set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -pedantic -Wconversion -g -Wno-unused-result")
include_directories(.)

add_executable(Assignment3
        driver.cpp
        rummikub.h rummikub.cpp)
