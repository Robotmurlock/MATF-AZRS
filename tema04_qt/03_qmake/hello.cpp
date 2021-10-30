#include "hello.hpp"
#include <iostream>

inline void hello()
{
    std::cout << "Hello World!" << std::endl;
}

void nhello(int n)
{
    for(unsigned i=0; i<n; i++)
        hello();
}