#include <iostream>
#include <vector>

int bruteforce_check(int n)
{
    int cnt = 0;
    for(int num=2; num<=n; num++)
    {
        int is_prime = 1;
        for(int i=2; i<num; i++)
            if(num % i == 0)
            {
                is_prime = 0;
                break;
            }
        cnt += is_prime;
    }
    return cnt;
}

int bruteforce_check_with_optimization(int n)
{
    int cnt = 0;
    for(int num=2; num<=n; num++)
    {
        int is_prime = 1;
        for(int i=2; 2*i<=num; i++)
            if(num % i == 0)
            {
                is_prime = 0;
                break;
            }
        cnt += is_prime;
    }
    return cnt;
}

int bruteforce_check_with_better_optimization(int n)
{
    int cnt = 0;
    for(int num=2; num<=n; num++)
    {
        int is_prime = 1;
        for(int i=2; i*i<=num; i++)
            if(num % i == 0)
            {
                is_prime = 0;
                break;
            }
        cnt += is_prime;
    }
    return cnt;
}

int smart_check(int n)
{
    int cnt = 0;
    for(int num=2; num<=n; num++)
    {
        int is_prime = 1;
        if(num > 3)
        {
            if((num%2 == 0) || (num%3 == 0))
            {
                is_prime = 0;
            }
            else
            {
                int i = 5;
                while(i*i <= num)
                {
                    if((num%i == 0) || (num%(i+2) == 0))
                    {
                        is_prime = 0;
                        break;
                    }
                    i += 6;
                }
            }
        }
        cnt += is_prime;
    }
    return cnt;
}

int sieve_of_eratosthenes(int n)
{
    std::vector<bool> inset(n+1, true);
    inset[0] = false;
    inset[1] = false;
    for(int i=2; i<=n; i++)
        if(inset[i])
            for(int j=2*i; j<=n; j+=i)
                inset[j] = false;

    int cnt;
    for(bool c: inset)
        cnt += c;
    return cnt;
}

int main()
{
    const int N = 100000;

    std::cout << "bruteforce_check: " << bruteforce_check(N) << std::endl;
    std::cout << "bruteforce_check_with_optimization: " << bruteforce_check_with_optimization(N) << std::endl;
    std::cout << "bruteforce_check_with_better_optimization: " << bruteforce_check_with_better_optimization(N) << std::endl;
    std::cout << "smart_check: " << smart_check(N) << std::endl;
    std::cout << "sieve_of_eratosthenes: " << sieve_of_eratosthenes(N) << std::endl;

    return 0;
}