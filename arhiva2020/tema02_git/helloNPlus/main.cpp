#include <iostream>

void hello()
{
    std::cout << "Hello Warld!" << std::endl;
}

void nPlusHello(unsigned n)
{
    while(n >= 0)
    {
        hello();
        n--;
    }
}

int main()
{
    int n;
    std::cin >> n;
    nPlusHello(n);
    return 0;
}