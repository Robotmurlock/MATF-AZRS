#include <iostream>
#include <vector>

int main()
{
    // Ako se postavi kursor misa preko npr. 'std::vector' i postoji offline cppreference
    // onda se sa desne strane u okviru qtcreator-a otvara dokumentacija
    // Napomena: Vrlo moguce da ovo nece raditi bez std namespace-a
    std::vector<int> vec{1, 2, 3, 4, 5};
    std::cout << "Hello World!" << std::endl;

    for(auto val: vec)
        std::cout << val << " ";
    std::cout << std::endl;

    return 0;
}
