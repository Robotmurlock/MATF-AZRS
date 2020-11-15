cmake_minimum_required(VERSION 3.16)
project(SplitLibrary VERSION 1.0.0)

add_library(
    string_library
    string_lib.hpp
    string_lib.cpp
)

add_executable(run_test test.cpp)

target_link_libraries(run_test PRIVATE string_library)