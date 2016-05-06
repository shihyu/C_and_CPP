
#include "8spl2.c"
#include "stdio.h"
main()
{
    int n, m, i;
    double s;
    double dy[12], ddy[12], z[8], dz[8], ddz[8];
    double x[12] = {0.52, 8.0, 17.95, 28.65, 50.65, 104.6,
                    156.6, 260.7, 364.4, 468.0, 507.0, 520.0
                   };
    double y[12] = {5.28794, 13.84, 20.2, 24.9, 31.1, 36.5,
                    36.6, 31.0, 20.9, 7.8, 1.5, 0.2
                   };
    double t[8] = {4.0, 14.0, 30.0, 60.0, 130.0, 230.0,
                   450.0, 515.0
                  };
    ddy[0] = -0.279319;
    ddy[11] = 0.011156;
    n = 12;
    m = 8;
    printf("\n");
    s = spl2(x, y, n, dy, ddy, t, m, z, dz, ddz);
    printf(
        "      x(i)          y(i)          dy(i)         ddy(i)\n");

    for (i = 0; i <= 11; i++) {
        printf("%14.5e%14.5e%14.5e%14.5e\n", x[i], y[i], dy[i], ddy[i]);
    }

    printf("\n");
    printf("s=%13.5e\n", s);
    printf("\n");
    printf(
        "      t(i)          z(i)          dz(i)         ddz(i)\n");

    for (i = 0; i <= 7; i++) {
        printf("%14.5e%14.5e%14.5e%14.5e\n", t[i], z[i], dz[i], ddz[i]);
    }

    printf("\n");
}

