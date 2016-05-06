
#include "stdio.h"
#include "8atk.c"
main()
{
    double t, z, eps;
    double x[11] = { -1.0, -0.8, -0.65, -0.4, -0.3,
                     0.0, 0.2, 0.4, 0.6, 0.8, 1.0
                   };
    double y[11] = {0.0384615, 0.0588236, 0.0864865, 0.2,
                    0.307692, 1.0, 0.5, 0.2, 0.1, 0.0588236, 0.0384615
                   };
    eps = 1.0e-6;
    printf("\n");
    t = -0.75;
    z = atk(x, y, 11, t, eps);
    printf("t=%6.3f,   z=%13.5e\n", t, z);
    t = 0.05;
    z = atk(x, y, 11, t, eps);
    printf("t=%6.3f,   z=%13.5e\n", t, z);
    printf("\n");
}

