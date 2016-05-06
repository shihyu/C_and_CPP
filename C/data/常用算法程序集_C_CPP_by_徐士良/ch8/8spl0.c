
#include "8spl.c"
#include "stdio.h"
main()
{
    int k, n;
    double t;
    double x[11] = { -1.0, -0.95, -0.75, -0.55, -0.3, 0.0,
                     0.2, 0.45, 0.6, 0.8, 1.0
                   };
    double y[11] = {0.0384615, 0.0424403, 0.06639, 0.116788,
                    0.307692, 1.0, 0.5, 0.164948, 0.1, 0.0588236, 0.0384615
                   };
    double s[5];
    k = -1;
    n = 11;
    printf("\n");
    t = -0.85;
    spl(x, y, n, k, t, s);
    printf("x=%6.3f,   f(x)=%13.5e\n", t, s[4]);
    printf("s0=%13.5e, s1=%13.5e, s2=%13.5e, s3=%13.5e\n", s[0], s[1], s[2], s[3]);
    printf("\n");
    t = 0.15;
    spl(x, y, n, k, t, s);
    printf("x=%6.3f,   f(x)=%13.5e\n", t, s[4]);
    printf("s0=%13.5e, s1=%13.5e, s2=%13.5e, s3=%13.5e\n", s[0], s[1], s[2], s[3]);
    printf("\n");
}

