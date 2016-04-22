#include "stdio.h"
#include "rp2va.c"
main()
{
    double r;
    static double a[4][3] = {{1.0, 2.0, 3.0}, {2.0, 3.0, 4.0},
        {3.0, 4.0, 5.0}, {5.0, 6.0, 7.0}
    };

    printf("\n");
    r = rp2va(a, 4, 3, 1.6, -1.4); /* 调用函数进行求解*/
    printf("A(1.60,-1.4)=%2.5f\n", r);
    printf("\n");
}
