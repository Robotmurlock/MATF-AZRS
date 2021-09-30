#include <iostream>
#include <thread>

int global_value = 0;

void inc_value()
{
    global_value++;
}

int main()
{
    std::thread thread(inc_value);
    global_value++;
    thread.join();
    
    std::cout << global_value << std::endl;

    return 0;
}

// Trka za resurse
// 1) jednom resursu pristupaju vise niti
// 2) barem jedna nit pise
// 3) ne postoji medjusobno iskljucivanje