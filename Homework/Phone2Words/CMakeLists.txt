cmake_minimum_required(VERSION 3.14)
project(Phone2Words)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -std=c++11 -pedantic -Wconversion -Wno-unused-result")

include_directories(.)

add_executable(Phone2Words
        driver.cpp
        phone2word.h phone2word.cpp)
