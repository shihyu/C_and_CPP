#include "stdio.h"
void main()
{
    int k;
    double x, z;
    z = 2.0;
    x = 0.0;

    for (k = 0; k < 10; k++) {
        x = x + 0.2;
    }

    printf("z=%2.17f\n", z);
    printf("x=%2.17f\n", x);
}
