#include <iostream>
#include <string>

int main()
{
    std::string a("Foo"), b("Baz");
    for (int i = 0; i < 20000; ++i) {
        a = a + "Bar" + b;
    }
    return 0;
}
