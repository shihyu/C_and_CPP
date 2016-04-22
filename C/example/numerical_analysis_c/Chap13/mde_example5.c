#include "stdio.h"
#include "stdlib.h"
#include "mde.c"
#define pi 3.1415926
void main()
{
    int L, j;
    double* rand;
    double x, mean, adev, sddev, var, skew, kurt;
    L = 100; /*生成100个随机数*/
    rand = (double*)malloc(sizeof(double) * L);

    if (rand == NULL) {
        printf("memory alloc failed.\n");
        exit(0);
    }

    for (j = 0; j < L; j++) {
        x = pi * j / L;
        rand[j] = sin(x);
    }

    mde(rand, L, &mean, &adev, &sddev, &var, &skew, &kurt);
    printf("Mean:    %1.5f\n", mean);
    printf("adev:    %1.5f\n", adev);
    printf("sddev:   %1.5f\n", sddev);
    printf("var:     %1.5f\n", var);
    printf("skew:    %1.5f\n", skew);
    printf("kurt:    %1.5f\n", kurt);
}
