cmake_minimum_required(VERSION 3.6)
project(linked_list)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp linked_list.cpp)
add_executable(linked_list ${SOURCE_FILES} linked_list.cpp)