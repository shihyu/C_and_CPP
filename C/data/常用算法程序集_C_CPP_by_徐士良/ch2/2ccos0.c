
#include "stdio.h"
#include "2ccos.c"
main()
{
    double x, y, u, v;
    x = 1.0;
    y = 4.0;
    ccos(x, y, &u, &v);
    printf("\n");
    printf("  %13.6e +j %13.6e\n", u, v);
    printf("\n");
}

