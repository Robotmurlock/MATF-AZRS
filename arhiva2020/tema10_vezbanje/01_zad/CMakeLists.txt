cmake_minimum_required(VERSION 3.16)
project(program VERSION 1.0.0)

add_library(
  lib1
  headers/lib1.hpp
  sources/lib1.cpp
)

add_library(
  lib2
  headers/lib2.hpp
  sources/lib2.cpp
)

add_executable(program main.cpp)

target_link_libraries(program PRIVATE lib1 lib2)
