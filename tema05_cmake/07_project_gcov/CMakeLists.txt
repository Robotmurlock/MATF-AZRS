cmake_minimum_required(VERSION 3.16)
project(MyProgram VERSION 1.0.0)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
enable_testing()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra --coverage")

add_subdirectory(string_lib)

add_executable(myprogram src/main.cpp)
add_executable(run_test string_lib/test.cpp)

add_test(
    NAME run_test
    COMMAND run_test
)

if(CMAKE_COMPILER_IS_GNUCXX)
    include(CodeCoverage)
    SETUP_TARGET_FOR_COVERAGE_LCOV(NAME coverage EXECUTABLE run_test)
endif()

target_link_libraries(myprogram PRIVATE string_lib)
target_link_libraries(run_test PRIVATE string_lib)
