
#include "stdio.h"
#include "1cply.c"
main()
{
    double x, y, u, v;
    double ar[4] = {2.0, 2.0, 1.0, 2.0};
    double ai[4] = {1.0, 1.0, 1.0, 2.0};
    printf("\n");
    x = 1.0;
    y = 1.0;
    cply(ar, ai, 4, x, y, &u, &v);
    printf("p(1.0+j1.0)=%10.7lf +j %10.7lf\n", u, v);
    printf("\n");
}

