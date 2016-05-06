
#include "stdio.h"
#include "2clog.c"
main()
{
    double x, y, u, v;
    x = 1.0;
    y = 4.0;
    clog(x, y, &u, &v);
    printf("\n");
    printf("  %13.6e +j %13.6e\n", u, v);
    printf("\n");
}

