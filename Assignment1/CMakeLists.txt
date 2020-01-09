cmake_minimum_required(VERSION 3.14)
project(Assignment1)

set(CMAKE_CXX_STANDARD 11)

include_directories(src)

add_executable(Assignment1
        src/driver.cpp
        src/ObjectAllocator.cpp
        src/ObjectAllocator.h
        src/PRNG.cpp
        src/PRNG.h)
