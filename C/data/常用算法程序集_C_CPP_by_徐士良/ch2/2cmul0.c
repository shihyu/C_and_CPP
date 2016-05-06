
#include "stdio.h"
#include "2cmul.c"
main()
{
    double u, v;
    cmul(-1.3, 4.5, 7.6, 3.6, &u, &v);
    printf("\n");
    printf("  u+jv=%10.7lf +j %10.7f\n", u, v);
    printf("\n");
}

