
#include "stdio.h"
#include "13lman.c"
main()
{
    int i, j, js;
    void eklm5();
    double p[3][3], x[200][3], y[200][1], g[3][1], t, s;
    double f[3][3] = {{1.0, 0.05, 0.00125},
        {0.0, 1.0, 0.05}, {0.0, 0.0, 1.0}
    };
    double q[3][3] = {{0.25, 0.0, 0.0},
        {0.0, 0.25, 0.0}, {0.0, 0.0, 0.25}
    };
    double r[1][1] = {0.25};
    double h[1][3] = {1.0, 0.0, 0.0};

    for (i = 0; i <= 2; i++)
        for (j = 0; j <= 2; j++) {
            p[i][j] = 0.0;
        }

    for (i = 0; i <= 199; i++)
        for (j = 0; j <= 2; j++) {
            x[i][j] = 0.0;
        }

    eklm5(200, y);

    for (i = 0; i <= 199; i++) {
        t = 0.05 * i;
        y[i][0] = 5.0 - 2.0 * t + 3.0 * t * t + y[i][0];
    }

    js = lman(3, 1, 200, f, q, r, h, y, x, p, g);

    if (js != 0) {
        printf("\n");
        printf("   t       s            y            ");
        printf("x(0)         x[1]         x(2)   \n");

        for (i = 0; i <= 199; i = i + 5) {
            t = 0.05 * i;
            s = 5.0 - 2.0 * t + 3.0 * t * t;
            printf("%6.2f  %13.5e  %13.5e  %13.5e  %13.5e  %13.5e\n",
                   t, s, y[i][0], x[i][0], x[i][1], x[i][2]);
        }

        printf("\n");
    }
}

static void eklm5(n, y)
int n;
double y[];
{
    int i, j, m;
    double s, w, v, r, t;
    s = 65536.0;
    w = 2053.0;
    v = 13849.0;
    r = 0.0;

    for (i = 0; i <= n - 1; i++) {
        t = 0.0;

        for (j = 0; j <= 11; j++) {
            r = w * r + v;
            m = (int)(r / s);
            r = r - m * s;
            t = t + r / s;
        }

        y[i] = 0.5 * (t - 6.0);
    }

    return;
}

