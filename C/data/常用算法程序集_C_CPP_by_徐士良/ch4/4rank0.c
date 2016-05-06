
#include "stdio.h"
#include "4rank.c"
main()
{
    double a[5][4] = { {1.0, 2.0, 3.0, 4.0},
        {5.0, 6.0, 7.0, 8.0},
        {9.0, 10.0, 11.0, 12.0},
        {13.0, 14.0, 15.0, 16.0},
        {17.0, 18.0, 19.0, 20.0}
    };
    printf("\n");
    printf("RANK=%d\n", rank(a, 5, 4));
    printf("\n");
}

