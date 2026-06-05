cmake_minimum_required(VERSION 2.4)

project(FirstContainers)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../include)

add_executable(vectortiming vectortiming.cpp)
add_executable(arraytest    arraytest.cpp)
add_executable(receiptbagtest receiptbagtest.cpp)