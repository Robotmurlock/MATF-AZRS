#include <fstream>
#include <string>
#include <iostream>

int main(int argc, char** argv)
{
    const std::string ispit1 = "indeks: mi22173, ocena: 7";
    const std::string ispit2 = "indeks: mi22174, ocena: 8";
    const std::string ispit3 = "indeks: mi22175, ocena: 9";
    const std::string ispit4 = "indeks: mi22176, ocena: 5";
    const std::string ispit5 = "indeks: mi22177, ocena: 7";

    std::ofstream database("/data/database.txt");

    database << ispit1 << std::endl;
    database << ispit2 << std::endl;
    database << ispit3 << std::endl;
    database << ispit4 << std::endl;
    database << ispit5 << std::endl;

    database.close();

    std::cout << "DONE" << std::endl;

    return 0;
}
