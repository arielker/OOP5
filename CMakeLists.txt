cmake_minimum_required(VERSION 3.0.0)

project(OOP5 LANGUAGES CXX)

set(OOP_FLAGS_DEBUG "-std=c++11 --pedantic-errors -Wall -Werror")
set(OOP_FLAGS_RELEASE "${OOP_FLAGS_DEBUG} -DNDEBUG")

set(CMAKE_C_FLAGS ${OOP_FLAGS_DEBUG})

add_executable(OOP5 part1/Part1Examples.cpp)