#include <string_lib.hpp>
#include <fstream>
#include <iostream>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "Usage: ./program [input_file]" << std::endl;
        return -1;
    }
    std::ifstream input(argv[1]);
    std::string line;
    unsigned lines_cnt = 0;
    unsigned words_cnt = 0;
    while(getline(input, line))
    {
        lines_cnt++;
        words_cnt += split(line, ' ').size();
    }

    std::cout << "Number of lines: " << lines_cnt << std::endl;
    std::cout << "Number of words: " << words_cnt << std::endl;
    return 0;
}