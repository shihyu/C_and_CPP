#include "stdio.h"
#include "smoth.c"
main()
{
    int i, n;
    double x[15] = {154.0, 245.0, 327.0, 259.0, 101.0,
                    142.0, 249.0, 312.0, 265.0, 117.0,
                    137.0, 253.0, 333.0, 287.0, 123.0
                   };
    double y[15];
    n = 15;
    smoth(x, n, y);
    printf("五点三次平滑：\n");

    for (i = 0; i < n; i++) {
        printf("x(%2d)=%4.1f   y(%2d)=%4.1f\n", i, x[i], i, y[i]);
    }

    printf("\n");
}
