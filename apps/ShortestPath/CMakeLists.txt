cmake_minimum_required(VERSION 2.4)

project(ShortestPathTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../include)

add_executable(shortestpath shortestpath.cpp)
