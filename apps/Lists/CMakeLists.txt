cmake_minimum_required(VERSION 2.4)


project(AssignmentTests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include_directories(../../include)


add_executable(listtest listtest.cpp)
add_executable(circularlisttest circularlisttest.cpp)