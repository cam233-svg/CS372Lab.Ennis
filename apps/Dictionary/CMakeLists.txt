cmake_minimum_required(VERSION 3.12)

project(dicttest)

# C++20 is required: Pair<Key,Value> uses the defaulted spaceship
# operator (operator<=>), a C++20 feature.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../include)

add_executable(dicttest dicttest.cpp)
