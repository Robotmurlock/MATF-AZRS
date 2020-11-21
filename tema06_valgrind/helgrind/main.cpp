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

    return 0;
}