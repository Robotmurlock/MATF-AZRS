cmake_minimum_required(VERSION 3.16)
project(MyProgram VERSION 1.0.0)

add_subdirectory(string_lib)

add_executable(myprogram src/main.cpp)
add_executable(run_test string_lib/test.cpp)

target_link_libraries(myprogram PRIVATE string_lib)
target_link_libraries(run_test PRIVATE string_lib)