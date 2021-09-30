#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    std::ifstream input("input.txt");
    if(input.fail())
    {
        std::cout << "Error: File \"input.txt\" is missing!\n" << std::endl;
        return -1;
    }
    int n;
    input >> n;
    if(n < 0)
    {
        printf("Error: Value of n negative!\n");
        return -1;
    }
    if(n == 1)
    {
        printf("Error: Minimum sample size is 2!\n");
        return -1;
    }

    double sum = 0.0;
    std::vector<double> xs(n);
    for(int i=0; i<n; i++)
    {
        double num;
        input >> num;
        if(num == 666)
        {
            printf("Error: By fire be purged!\n");
            return -1;
        }
        xs[i] = num;
        sum += num;
    }

    double mean = sum/n;
    double std_sum = 0.0;
    for(int i=0; i<n; i++)
        std_sum += pow(xs[i] - mean, 2);

    double std = sqrt(std_sum/(n-1));

    printf("mean=%lf\n", mean);
    printf("std=%lf\n", std);
    return 0;
}