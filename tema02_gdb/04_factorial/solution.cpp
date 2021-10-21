#include <iostream>

int a = 3, b = 5, c = 7;

int factorial(int n)
{
    int sol = 1;
    do 
    {
        a = a*c - b;
        sol *= n;
        b = 3*c - a;
        c = 20*a - 7*(a-b+c*c);
        n--;
    } while(n);
    return sol;
}

int main()
{
    std::cout << "5! = " << factorial(5) << std::endl;  
    return 0;
}
