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

    // Act
    const std::vector<std::string> result1 = split(data, del1);;
    const std::vector<std::string> result2 = split(data, del2); ;
    const std::vector<std::string> result3 = split(data, del3);
    const std::vector<std::string> result4 = split(empty, del2);
    const std::vector<std::string> result5 = split(all_dels, del3);
    const std::vector<std::string> result6 = split(mlt_dels, del2);

    // Assert
    const std::vector<std::string> expected_result1 = std::vector<std::string>{"hello", "darkness,", "my", "old", "friend!"};
    const std::vector<std::string> expected_result2 = std::vector<std::string>{"hello darkness", " my old friend!"};
    const std::vector<std::string> expected_result3 = split(data, del3);
    const std::vector<std::string> expected_result4 = split(empty, del2);
    const std::vector<std::string> expected_result5 = split(all_dels, del3);
    const std::vector<std::string> expected_result6 = split(mlt_dels, del2);

    assert(result1 == expected_result1);
    assert(result2 == expected_result2);
    assert(result3 == std::vector<std::string>{"hello darkness, my old friend!"});
    assert(result4 == std::vector<std::string>{});
    assert(result5 == std::vector<std::string>{});
    assert(result6 == std::vector<std::string>{"hello darkness", " my old friend!"});

    std::cout << "Tests passed!" << std::endl;

    return 0;
}