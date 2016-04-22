#include "stdio.h"
#include "math.h"
#include "gammln.c"
#include "beta.c"
void main()
{
    int i;
    double x, y, z;
    printf("Gamma(x): \n");

    for (i = 1; i < 10; i++) {
        x = 1.5 * i;
        y = gammln(x);
        y = exp(y);
        printf("x=%2.5f, gamma(x)=%2.5f\n", x, y);
    }

    printf("\n");
    printf("Beta(x,y): \n");

    for (i = 1; i < 5; i++) {
        x = 0.5 * i;
        y = 1.5 * i;
        z = beta(x, y);
        printf("x=%2.5f,y=%2.5f, beta(x)=%2.5f\n", x, y, z);
    }

    getchar();
}

