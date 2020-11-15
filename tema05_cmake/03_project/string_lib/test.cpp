#include "string_lib.hpp"
#include <iostream>
#include <cassert>

int main()
{
    // Arange
    const std::string data     = "hello darkness, my old friend!";
    const std::string empty    = "";
    const std::string all_dels = "#########";
    const std::string mlt_dels = "hello darkness,,, my old friend!";
    const char del1 = ' ';
    const char del2 = ',';
    const char del3 = '#';

    // Arrange
    const std::vector<std::string> expected_result1{"hello", "darkness,", "my", "old", "friend!"};
    const std::vector<std::string> expected_result2{"hello darkness", " my old friend!"};
    const std::vector<std::string> expected_result3{"hello darkness, my old friend!"};
    const std::vector<std::string> expected_result4{};
    const std::vector<std::string> expected_result5{};
    const std::vector<std::string> expected_result6{"hello darkness", " my old friend!"};

    // Assert
    assert(split(data, del1) == expected_result1);
    assert(split(data, del2) == expected_result2);
    assert(split(data, del3) == expected_result3);
    assert(split(empty, del2) == expected_result4);
    assert(split(all_dels, del3) == expected_result5);
    assert(split(mlt_dels, del2) == expected_result6);

    std::cout << "Tests passed!" << std::endl;

    return 0;
}