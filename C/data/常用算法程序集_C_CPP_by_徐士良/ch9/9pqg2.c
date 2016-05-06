
#include "math.h"
double pqg2(a, b, eps, ss, f)
double a, b, eps, (*f)();
void (*ss)();
{
    int m, n, k, l, j;
    double pqg1();
    double bb[10], h[10], hh, s1, s2, t1, t2, x, g, s0, ep, s;
    m = 1;
    n = 1;
    hh = b - a;
    h[0] = hh;
    s1 = pqg1(a, eps, ss, f);
    s2 = pqg1(b, eps, ss, f);
    t1 = hh * (s1 + s2) / 2.0;
    s0 = t1;
    bb[0] = t1;
    ep = 1.0 + eps;

    while ((ep >= eps) && (m <= 9)) {
        t2 = 0.5 * t1;

        for (k = 0; k <= n - 1; k++) {
            x = a + (k + 0.5) * hh;
            s1 = pqg1(x, eps, ss, f);
            t2 = t2 + 0.5 * s1 * hh;
        }

        m = m + 1;
        h[m - 1] = h[m - 2] / 2.0;
        g = t2;
        l = 0;
        j = 2;

        while ((l == 0) && (j <= m)) {
            s = g - bb[j - 2];

            if (fabs(s) + 1.0 == 1.0) {
                l = 1;
            } else {
                g = (h[m - 1] - h[j - 2]) / s;
            }

            j = j + 1;
        }

        bb[m - 1] = g;

        if (l != 0) {
            bb[m - 1] = 1.0e+35;
        }

        s = bb[m - 1];

        for (j = m; j >= 2; j--) {
            s = bb[j - 2] - h[j - 2] / s;
        }

        ep = fabs(s - s0) / (1.0 + fabs(s));
        n = n + n;
        t1 = t2;
        s0 = s;
        hh = hh / 2.0;
    }

    return (s);
}

static double pqg1(x, eps, ss, f)
double x, eps, (*f)();
void (*ss)();
{
    int m, n, k, l, j;
    double b[10], h[10], y[2], hh, t1, t2, s0, yy, g, ep, s;
    m = 1;
    n = 1;
    (*ss)(x, y);
    hh = y[1] - y[0];
    h[0] = hh;
    t1 = 0.5 * hh * ((*f)(x, y[0]) + (*f)(x, y[1]));
    s0 = t1;
    b[0] = t1;
    ep = 1.0 + eps;

    while ((ep >= eps) && (m <= 9)) {
        t2 = 0.5 * t1;

        for (k = 0; k <= n - 1; k++) {
            yy = y[0] + (k + 0.5) * hh;
            t2 = t2 + 0.5 * hh * (*f)(x, yy);
        }

        m = m + 1;
        h[m - 1] = h[m - 2] / 2.0;
        g = t2;
        l = 0;
        j = 2;

        while ((l == 0) && (j <= m)) {
            s = g - b[j - 2];

            if (fabs(s) + 1.0 == 1.0) {
                l = 1;
            } else {
                g = (h[m - 1] - h[j - 2]) / s;
            }

            j = j + 1;
        }

        b[m - 1] = g;

        if (l != 0) {
            b[m - 1] = 1.0e+35;
        }

        s = b[m - 1];

        for (j = m; j >= 2; j--) {
            s = b[j - 2] - h[j - 2] / s;
        }

        ep = fabs(s - s0) / (1.0 + fabs(s));
        n = n + n;
        t1 = t2;
        s0 = s;
        hh = 0.5 * hh;
    }

    return (s);
}

