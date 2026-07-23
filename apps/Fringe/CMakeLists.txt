cmake_minimum_required(VERSION 2.4)

project(FringeTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../include)

add_executable(fringetest fringetest.cpp)
