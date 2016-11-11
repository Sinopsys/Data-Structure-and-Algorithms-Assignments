cmake_minimum_required(VERSION 3.6)
project(Quiq_Sort)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp quick_sort.h)
add_executable(Quiq_Sort ${SOURCE_FILES})