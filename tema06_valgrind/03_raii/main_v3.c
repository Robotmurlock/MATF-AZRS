#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define OKAY       0
#define NEGATIVE_N 1
#define SMALL_N    2
#define EVIL       4

void check_status(int status)
{
    if(status & NEGATIVE_N)
    {
        printf("Error: Value of n negative!\n");
        exit(-1);
    }
    if(status & SMALL_N)
    {
        printf("Error: Minimum sample size is 2!\n");
        exit(-1);
    }
    if(status & EVIL)
    {
        printf("Error: By fire be purged!\n");
        exit(-1);
    }
}

int main()
{
    char* file_name = "input.txt";
    FILE* input = fopen(file_name, "r");
    if(input == NULL)
    {
        printf("Error: File \"input.txt\" is missing!\n");
        return -1;
    }

    int status = OKAY;
    int n;
    fscanf(input, "%d", &n);
    if(n < 0)
        status |= NEGATIVE_N;
    if(n == 1)
        status |= SMALL_N;

    double sum = 0.0;
    double* xs = malloc(n*sizeof(double));
    for(int i=0; i<n; i++)
    {
        double num;
        fscanf(input, "%lf", &num);
        if(num == 666)
            status |= EVIL;
        xs[i] = num;
        sum += num;
    }

    double mean = sum/n;
    double std_sum = 0.0;
    for(int i=0; i<n; i++)
        std_sum += pow(xs[i] - mean, 2);

    double std = sqrt(std_sum/(n-1));

    free(xs);
    fclose(input);

    check_status(status);

    printf("mean=%lf\n", mean);
    printf("std=%lf\n", std);
    return 0;
}