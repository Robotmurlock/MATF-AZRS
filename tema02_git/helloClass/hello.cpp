#include "hello.hpp"

#include <iostream>

void Hello::hey() const
{
    for(int i=0; i<m_val; i++)
        std::cout << "Hello World!" << std::endl;
}