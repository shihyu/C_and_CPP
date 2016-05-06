
#include "stdio.h"
#include "15topo.c"
main()
{
    int p[7], i;
    static int r1[8][2] = { {3, 1}, {3, 2}, {4, 6}, {4, 7},
        {5, 4}, {5, 6}, {5, 7}, {6, 7}
    };
    static int r2[6][2] = { {3, 1}, {3, 2}, {2, 7},
        {4, 5}, {5, 6}, {6, 4}
    };
    printf("\n");
    topo(7, r1, 8, p);

    for (i = 0; i <= 6; i++) {
        printf("%d  ", p[i]);
    }

    printf("\n\n");
    topo(7, r2, 6, p);

    for (i = 0; i <= 6; i++) {
        printf("%d  ", p[i]);
    }

    printf("\n\n");
}

