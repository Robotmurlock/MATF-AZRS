#include <iostream>
#include <string>
#include <thread>
#include <mutex>

class Resource{
private:
    // ...
public:
    void use() {};
};

Resource r1, r2;
std::mutex r1_lock, r2_lock, cout_lock;

void tprint(const std::string&name, const std::string& msg)
{
    cout_lock.lock();
    std::cout << "[" << name << "]: " << msg << std::endl;
    cout_lock.unlock();
}

void f(const std::string& name)
{
    tprint(name, "Started!");
    for(int i=0; i<10000; i++)
    {
        std::this_thread::sleep_for (std::chrono::milliseconds(1));
        tprint(name, "Locking r1!");
        r1_lock.lock();
        tprint(name, "Locking r2!");
        r2_lock.lock();
        tprint(name, "Doing my job...");
        r1.use();
        r2.use();
        tprint(name, "Unlocking r1!");
        r1_lock.unlock();
        tprint(name, "Unlocking r2!");
        r2_lock.unlock();
    }
    tprint(name, "Ended!");
}

void g(const std::string& name)
{
    tprint(name, "Started!");
    for(int i=0; i<10000; i++)
    {
        std::this_thread::sleep_for (std::chrono::milliseconds(1));
        tprint(name, "Locking r2!");
        r2_lock.lock();
        tprint(name, "Locking r1!");
        r1_lock.lock();
        tprint(name, "Doing my job...");
        r1.use();
        r2.use();
        tprint(name, "Unlocking r2!");
        r2_lock.unlock();
        tprint(name, "Unlocking r1!");
        r1_lock.unlock();
    }
    tprint(name, "Ended!");
}

void stop()
{
    std::this_thread::sleep_for (std::chrono::seconds(30));
    exit(EXIT_FAILURE);
}

int main()
{
    std::thread t1(f, "Thread01"), t2(g, "Thread02");
    std::thread deadlock_safety(stop);

    t1.join();
    t2.join();
    deadlock_safety.join();

    return 0;
}