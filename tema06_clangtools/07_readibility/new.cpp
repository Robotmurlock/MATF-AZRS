#include <iostream>
#include <stack>

int main()
{
    std::stack<int> s;
    s.push(3);
    s.push(8);
    s.push(9);
    s.push(7);

    while(!s.empty())
    {
        std::cout << s.top() << " ";
        s.pop();
    }

    return 0;
}
