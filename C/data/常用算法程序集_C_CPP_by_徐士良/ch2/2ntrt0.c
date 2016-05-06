
#include "stdio.h"
#include "2ntrt.c"
main()
{
    int n;
    double x, y, u[5], v[5];
    x = 1.0;
    y = 1.0;
    ntrt(x, y, 5, u, v);
    printf("\n");

    for (n = 0; n <= 4; n++) {
        printf(" n=%3d    %13.6e +j %13.6e\n", n, u[n], v[n]);
    }

    printf("\n");
}

