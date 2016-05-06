
#include "stdlib.h"
#include "math.h"
void pbs(t, h, n, y, eps, f)
void (*f)();
int n;
double t, h, eps, y[];
{
    void  rkt();
    int i, j, k, m, nn, it;
    double x, hh, dd, q, p, g[10], *b, *d, *u, *v, *w, *e;
    b = malloc(10 * n * sizeof(double));
    d = malloc(n * sizeof(double));
    u = malloc(n * sizeof(double));
    v = malloc(n * sizeof(double));
    w = malloc(n * sizeof(double));
    e = malloc(n * sizeof(double));

    for (j = 0; j <= n - 1; j++) {
        v[j] = y[j];
    }

    x = t;
    nn = 1;
    hh = h;
    g[0] = hh;
    rkt(x, hh, n, y, w, d, e, f);

    for (j = 0; j <= n - 1; j++) {
        b[j] = y[j];
        u[j] = y[j];
    }

    k = 1;
    it = 1;

    while (it == 1) {
        nn = nn + nn;
        hh = hh / 2.0;
        it = 0;
        g[k] = hh;

        for (j = 0; j <= n - 1; j++) {
            y[j] = v[j];
        }

        t = x;

        for (j = 0; j <= nn - 1; j++) {
            rkt(t, hh, n, y, w, d, e, f);
            t = t + hh;
        }

        for (j = 0; j <= n - 1; j++) {
            dd = y[j];
            m = 0;

            for (i = 0; i <= k - 1; i++)
                if (m == 0) {
                    q = dd - b[i * n + j];

                    if (fabs(q) + 1.0 == 1.0) {
                        m = 1;
                    } else {
                        dd = (g[k] - g[i]) / q;
                    }
                }

            b[k * n + j] = dd;

            if (m != 0) {
                b[k * n + j] = 1.0e+35;
            }
        }

        for (j = 0; j <= n - 1; j++) {
            dd = 0.0;

            for (i = k - 1; i >= 0; i--) {
                dd = -g[i] / (b[(i + 1) * n + j] + dd);
            }

            y[j] = dd + b[j];
        }

        p = 0.0;

        for (j = 0; j <= n - 1; j++) {
            q = fabs(y[j] - u[j]);

            if (q > p) {
                p = q;
            }
        }

        if ((p >= eps) && (k < 7)) {
            for (j = 0; j <= n - 1; j++) {
                u[j] = y[j];
            }

            k = k + 1;
            it = 1;
        }
    }

    free(b);
    free(d);
    free(u);
    free(v);
    free(w);
    free(e);
    return;
}

static void rkt(t, h, n, y, b, d, e, f)
void (*f)();
int n;
double t, h, y[], b[], d[], e[];
{
    int i, k;
    double a[4], tt;
    a[0] = h / 2.0;
    a[1] = a[0];
    a[2] = h;
    a[3] = h;
    (*f)(t, y, n, d);

    for (i = 0; i <= n - 1; i++) {
        b[i] = y[i];
        e[i] = y[i];
    }

    for (k = 0; k <= 2; k++) {
        for (i = 0; i <= n - 1; i++) {
            y[i] = e[i] + a[k] * d[i];
            b[i] = b[i] + a[k + 1] * d[i] / 3.0;
        }

        tt = t + a[k];
        (*f)(tt, y, n, d);
    }

    for (i = 0; i <= n - 1; i++) {
        y[i] = b[i] + h * d[i] / 6.0;
    }

    return;
}

