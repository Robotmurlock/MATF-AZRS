cmake_minimum_required(VERSION 3.16)
project(TidyMake VERSION 1.0.0)

add_library(
    sorty
    sort.hpp
    sort.cpp
)

add_executable(run main.cpp)

target_compile_features(run PRIVATE cxx_std_17)

target_link_libraries(run PRIVATE sorty)
