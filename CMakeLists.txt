cmake_minimum_required(VERSION 3.0.0)
project(task VERSION 0.1.0 LANGUAGES C CXX)

set(GOOGLETEST_VERSION 1.10.0)

add_executable(task main.cpp)
target_link_libraries(task gtest gmock pthread)
