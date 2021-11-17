#include "string_lib.hpp"
#include <iostream>
#include <cassert>

void test_split_space()
{
    // Arrange
    const std::string data = "hello darkness, my old friend!";
    const std::vector<std::string> expected_result{"hello", "darkness,", "my", "old", "friend!"};

    // Act
    const auto result = split(data, ' ');
    
    // Assert
    assert(result == expected_result);
}

void test_split_comma()
{
    // Arrange
    const std::string data = "hello darkness, my old friend!";
    const std::vector<std::string> expected_result{"hello darkness", " my old friend!"};

    // Act
    const auto result = split(data, ',');
    
    // Assert
    assert(result == expected_result);
}

void test_split_hash()
{
    // Arrange
    const std::string data = "hello darkness, my old friend!";
    const std::vector<std::string> expected_result{"hello darkness, my old friend!"};

    // Act
    const auto result = split(data, '#');
    
    // Assert
    assert(result == expected_result);
}

void test_split_empty()
{
    // Arrange
    const std::string empty = "";
    const std::vector<std::string> expected_result{};

    // Act
    const auto result = split(empty, ' ');
    
    // Assert
    assert(result == expected_result);
}

void test_split_all_hash()
{
    // Arrange
    const std::string hashes = "#################";
    const std::vector<std::string> expected_result{};

    // Act
    const auto result = split(hashes, '#');
    
    // Assert
    assert(result == expected_result);
}

void test_split_multiple_commas()
{
    // Arrange
    const std::string data = "hello darkness,,, my old friend!";
    const std::vector<std::string> expected_result{"hello darkness", " my old friend!"};

    // Act
    const auto result = split(data, ',');
    
    // Assert
    assert(result == expected_result);
}

int main()
{
    test_split_space();
    test_split_comma();
    test_split_hash();
    test_split_empty();
    test_split_all_hash();
    test_split_multiple_commas();

    std::cout << "Tests passed!" << std::endl;
    return 0;
}
