cmake_minimum_required(VERSION 3.16)
project(MyProgram VERSION 1.0.0)

add_subdirectory(string_lib)

add_executable(myprogram src/main.cpp)

target_link_libraries(myprogram PRIVATE string_lib)