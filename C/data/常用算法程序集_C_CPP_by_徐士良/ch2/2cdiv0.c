
#include "stdio.h"
#include "2cdiv.c"
main()
{
    double u, v;
    cdiv(-1.3, 4.5, 7.6, -3.6, &u, &v);
    printf("\n");
    printf(" u+jv=%10.7f +j %10.7f", u, v);
    printf("\n");
}

