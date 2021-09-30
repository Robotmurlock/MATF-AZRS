#include <iostream>
#include <cstring>

int main(int argc, char** argv)
{
    if(argc < 2)
    {
        std::cout << "Wrong number of arguments!" << std::endl;
        return -1;
    }

    int n = atoi(argv[1]);
    for(int i=0; i<n; i++)
        std::cout << "Hello World!" << std::endl;

    return 0;
}