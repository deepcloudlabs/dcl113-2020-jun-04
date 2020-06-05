cmake_minimum_required(VERSION 3.16)
project(module02)

set(CMAKE_CXX_STANDARD 17)

add_executable(module02 main.cpp)
add_executable(exercise exercise.cpp person.h)