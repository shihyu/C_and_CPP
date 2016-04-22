#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include "randgsabs.c"
void main()
{
    int L = 100, i, j;
    double a, b;
    double* G = (double*)malloc(L * sizeof(double));

    if (G == NULL) {
        printf("memory alloc failed.\n");
        exit(0);
    }

    a = 3.0;                       /* 均值*/
    b = 2.2;                        /* 方差*/
    randgsabs(L, a, b, G);     /* 调用函数*/

    for (i = 0; i < 20; i++) {
        for (j = 0; j < 5; j++) {
            printf("%5.4f ", G[i * 5 + j]);
        }

        printf("\n");
    }
}
