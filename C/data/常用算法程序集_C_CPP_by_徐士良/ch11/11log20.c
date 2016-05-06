
#include "stdio.h"
#include "11log2.c"
main()
{
    int n;
    double a[7];
    double x[10] = {0.1, 1.0, 3.0, 5.0, 8.0, 10.0,
                    20.0, 50.0, 80.0, 100.0
                   };
    double y[10] = {0.1, 0.9, 2.5, 4.0, 6.3, 7.8,
                    14.8, 36.0, 54.0, 67.0
                   };
    n = 10;
    log2(n, x, y, a);
    printf("\n");
    printf("a=%13.6e   b=%13.6e  \n", a[1], a[0]);
    printf("\n");
    printf("q=%13.6e   s=%13.6e  \n", a[2], a[3]);
    printf("\n");
    printf("umax=%13.6e  umin=%13.6e  u=%13.6e \n",
           a[4], a[5], a[6]);
    printf("\n");
}

