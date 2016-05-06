
#include "stdio.h"
#include "8hmt.c"
main()
{
    int i;
    double t, z;
    double x[10] = {0.1, 0.15, 0.3, 0.45, 0.55, 0.6, 0.7, 0.85, 0.9, 1.0};
    double y[10] = {0.904837, 0.860708, 0.740818, 0.637628, 0.576950,
                    0.548812, 0.496585, 0.427415, 0.406570, 0.367879
                   };
    double dy[10];
    printf("\n");

    for (i = 0; i <= 9; i++) {
        dy[i] = -y[i];
    }

    t = 0.356;
    z = hmt(x, y, dy, 10, t);
    printf("t=%6.3f,   z=%13.5e\n", t, z);
    printf("\n");
}

