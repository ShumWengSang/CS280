cmake_minimum_required(VERSION 3.14)
project(catalan)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra -std=c++11 -pedantic -Weffc++ -Wold-style-cast -Woverloaded-virtual -Wsign-promo  -Wctor-dtor-privacy -Wnon-virtual-dtor -Wreorder")
include_directories(.)

add_executable(catalan
        catalan.cpp
        catalan.h
        driver.cpp)
