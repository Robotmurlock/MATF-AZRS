#include <cstdio>
#include <cstdlib>
#include <cmath>

struct raii_file{
    FILE* m_file;

    raii_file(const char* file_name)
    {
        m_file = fopen(file_name, "r");
        if(m_file == NULL)
        {
            printf("Error: File \"input.m_file.txt\" is missing!\n");
            exit(-1);
        }
    }
    ~raii_file()
    {
        free(m_file);
    }
};

struct raii_array{
    double* m_arr;

    raii_array(int n)
    {
        m_arr = (double*)malloc(n*sizeof(double));
        if(m_arr == NULL)
        {
            printf("Errof: Failed to allocate!");
            exit(-1);
        }
    }
    ~raii_array()
    {
        free(m_arr);
    }
};

int main()
{
    raii_file input("input.txt");
    int n;
    fscanf(input.m_file, "%d", &n);
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
    raii_array xs(n);
    for(int i=0; i<n; i++)
    {
        double num;
        fscanf(input.m_file, "%lf", &num);
        if(num == 666)
        {
            printf("Error: By fire be purged!\n");
            return -1;
        }
        xs.m_arr[i] = num;
        sum += num;
    }

    double mean = sum/n;
    double std_sum = 0.0;
    for(int i=0; i<n; i++)
        std_sum += pow(xs.m_arr[i] - mean, 2);

    double std = sqrt(std_sum/(n-1));

    printf("mean=%lf\n", mean);
    printf("std=%lf\n", std);
    return 0;
}