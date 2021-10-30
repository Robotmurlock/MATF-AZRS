cmake_minimum_required(VERSION 3.16)
project(HelloWorld VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O2")

add_executable(hello main.cpp)
