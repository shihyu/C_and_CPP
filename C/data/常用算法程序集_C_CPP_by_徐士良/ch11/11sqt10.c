
#include "stdio.h"
#include "11sqt1.c"
main()
{
    double dt[6], a[2];
    double x[11] = { 0.0, 0.1, 0.2, 0.3, 0.4, 0.5,
                     0.6, 0.7, 0.8, 0.9, 1.0
                   };
    double y[11] = { 2.75, 2.84, 2.965, 3.01, 3.20,
                     3.25, 3.38, 3.43, 3.55, 3.66, 3.74
                   };
    sqt1(x, y, 11, a, dt);
    printf("\n");
    printf("a=%13.5e   b=%13.5e\n", a[1], a[0]);
    printf("\n");
    printf("q=%13.5e  s=%13.5e  p=%13.5e\n", dt[0], dt[1], dt[2]);
    printf("\n");
    printf("umax=%13.5e umin=%13.5e  u=%13.5e\n", dt[3], dt[4], dt[5]);
    printf("\n");
}

