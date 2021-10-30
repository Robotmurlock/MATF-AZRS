add_library(
    string_lib
    string_lib.hpp
    string_lib.cpp
)

target_include_directories(string_lib PUBLIC "$(CMAKE_CURRENT_SOURCE_DIR)")