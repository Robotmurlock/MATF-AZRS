#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include "voronoi.hpp"

void check(bool cond, const std::string& msg)
{
    if(!cond)
    {
        std::cerr << msg << std::endl;
        exit(EXIT_FAILURE);
    }
}

bool test_compare_files(int test_id, std::string &filename1, std::string &filename2)
{
    std::string tid = std::to_string(test_id);
    std::ifstream file1(filename1), file2(filename2);
    check(!file1.fail() && !file2.fail(),
          "TEST " + tid + " FAILED: Opening files failed!");


    int line_index = 0;
    std::string line1, line2;
    while(true)
    {
        std::getline(file1, line1);
        std::getline(file2, line2);
        if(!file1.good())
        {
            check(!file2.good(),
                  "TEST " + tid + " FAILED: Mismatch on line "
                  + std::to_string(line_index) + "!");
            file1.close();
            file2.close();
            return true;
        }
        check(line1.length() == line2.length(),
              "TEST " + tid + " FAILED: Lines length mismatch on line "
              + std::to_string(line_index) + "!");
        for(unsigned i=0; i<line1.length(); i++)
            check(line1[i] == line2[i],
                  "TEST " + tid + " FAILED: Character mismatch on line "
                  + std::to_string(line_index) + ", index "
                  + std::to_string(i) + "!");
        line_index += 1;
    }
    return false;
}

void test()
{
    const int n_test = 5;
    for(int i=0; i<n_test; i++)
    {
        auto specification = Specification(i, i);
        voronoi(specification);

        auto sid = std::to_string(specification.id);
        std::string output_filename = "output" + sid + ".txt";
        std::string test_filename = "testovi/test" + sid + ".txt";
        check(test_compare_files(i, output_filename, test_filename), 
          "TEST " + std::to_string(i) + " FAILED!");
    }
    std::cerr << "ALL TESTS PASSED!" << std::endl;
}

int main(int argc, char** argv)
{
    check(argc >= 2, "Error: Wrong number of arguments: Usage: ./<program> <count>");
    if(strcmp(argv[1], "test") == 0)
    {
        test();
        return 0;
    }

    int count = std::atoi(argv[1]);
    srand(time(NULL));

    std::vector<Specification> specifications;
    for(int i=0; i<count; i++)
        specifications.emplace_back(i, rand());

    for(auto specification: specifications)
        voronoi(specification);

    return 0;
}
