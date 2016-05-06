
#include "stdio.h"
#include "3rnd1.c"
main()
{
    int i;
    double r;
    r = 5.0;
    printf("\n");

    for (i = 0; i <= 9; i++) {
        printf("%10.7lf\n", rnd1(&r));
    }

    printf("\n");
}

