#include <iostream>
#include <fstream>
#include <vector>
#include "vector_extension.hpp"

int main()
{
    // test load
    std::ifstream input("input.txt");
    auto v = load(input);

    std::cout << "duplicates(" << nduplicates(v) 
              << ") + uniques(" << nunique(v) 
              << ") == " << v.size() << std::endl;
    
    v = drop_duplicates(v);

    // test store
    std::ofstream output("output.txt");
    store(v, output);

    // test transfer
    std::ifstream another_input("input.txt");
    std::ofstream another_output("transfered.txt");
    transfer(another_input, another_output);
    return 0;    
}
