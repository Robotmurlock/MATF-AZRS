#include <iostream>
#include <thread>

void hello()
{
    std::cout << "Hello World!" << std::endl;
}

int main()
{
    // Pravi se objekat niti koji odmah zapocinje rad f-je hello()
    std::thread helloThread(hello);
    helloThread.join();
    return 0;
}