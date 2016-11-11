cmake_minimum_required(VERSION 3.6)
project(River_Problem)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp RiverProblem.cpp RiverProblem.h)
add_executable(River_Problem ${SOURCE_FILES})