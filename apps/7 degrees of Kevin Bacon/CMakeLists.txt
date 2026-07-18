cmake_minimum_required(VERSION 3.11)

project(GraphAssignment)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(../../include
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/source)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(simplecycle simplecycle.cpp)
target_link_libraries(simplecycle gtest_main)

include(GoogleTest)
gtest_discover_tests(simplecycle)

add_executable(baconnumber baconnumber.cpp)
target_link_libraries(baconnumber gtest_main)

include(GoogleTest)
gtest_discover_tests(baconnumber)
