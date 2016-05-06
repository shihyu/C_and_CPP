
#include "stdio.h"
#include "4sdet.c"
main()
{
    double a[4][4] = { {1.0, 2.0, 3.0, 4.0},
        {5.0, 6.0, 7.0, 8.0},
        {9.0, 10.0, 11.0, 12.0},
        {13.0, 14.0, 15.0, 16.0}
    };
    double b[4][4] = { {3.0, -3.0, -2.0, 4.0},
        {5.0, -5.0, 1.0, 8.0},
        {11.0, 8.0, 5.0, -7.0},
        {5.0, -1.0, -3.0, -1.0}
    };
    double det;
    det = sdet(a, 4);
    printf("det(A)=%13.6e\n", det);
    printf("\n");
    det = sdet(b, 4);
    printf("det(B)=%13.6e\n", det);
    printf("\n");
}

