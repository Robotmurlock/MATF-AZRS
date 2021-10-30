cmake_minimum_required(VERSION 3.16)
project(HelloWorld VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra")

add_executable(hello main.cpp)
