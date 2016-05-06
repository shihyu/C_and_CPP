
#include "stdio.h"
#include "13four.c"
main()
{
    int i;
    double f[101], a[51], b[51], c, h;
    h = 6.283185306 / 101.0;

    for (i = 0; i <= 100; i++) {
        c = (i + 0.5) * h;
        f[i] = c * c;
    }

    four(f, 50, a, b);
    printf("\n");

    for (i = 0; i <= 50; i++) {
        printf("a(%3d)=%13.5e   b(%3d)=%13.5e\n", i, a[i], i, b[i]);
    }

    printf("\n");
}

