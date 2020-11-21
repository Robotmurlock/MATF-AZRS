#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    FILE* input = fopen("input.txt", "r");
    if(input == NULL)
    {
        printf("Error: File \"input.txt\" is missing!\n");
        return -1;
    }
    int n;
    fscanf(input, "%d", &n);
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
    double* xs = malloc(n*sizeof(double));
    for(int i=0; i<n; i++)
    {
        double num;
        fscanf(input, "%lf", &num);
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

    free(xs);
    fclose(input);

    printf("mean=%lf\n", mean);
    printf("std=%lf\n", std);
    return 0;
}