#include "stdio.h"
#include "math.h"

void SVDcmp(double a[][3], int m, int n, double* w, double v[][3])
{
    /* BUG `nm' may be used uninitialized in this function */
    int flag, i, its, j, jj, k, l, nm, nm1 = n - 1, mm1 = m - 1;
    double c, f, h, s, x, y, z;
    double anorm = 0.0, g = 0.0, scale = 0.0;
    double* rv1;

    if (m < n) {
        Print("SVDCMP: You must augment A with extra zero rows");
    }

    rv1 = (double*) ralloc((unsigned) n * sizeof(double));

    /* Householder reduction to bidigonal form */
    for (i = 0; i < n; i++) {
        l = i + 1;
        rv1[i] = scale * g;
        g = s = scale = 0.0;

        if (i < m) {
            for (k = i; k < m; k++) {
                scale += fabs(a[k][i]);
            }

            if (scale) {
                for (k = i; k < m; k++) {
                    a[k][i] /= scale;
                    s += a[k][i] * a[k][i];
                }

                f = a[i][i];
                g = -sign(sqrt(s), f);
                h = f * g - s;
                a[i][i] = f - g;

                if (i != nm1) {
                    for (j = l; j < n; j++) {
                        for (s = 0.0, k = i; k < m; k++) {
                            s += a[k][i] * a[k][j];
                        }

                        f = s / h;

                        for (k = i; k < m; k++) {
                            a[k][j] += f * a[k][i];
                        }
                    }
                }

                for (k = i; k < m; k++) {
                    a[k][i] *= scale;
                }
            }
        }

        w[i] = scale * g;
        g = s = scale = 0.0;

        if (i < m & amt; &amt; i != nm1) {
            for (k = l; k < n; k++) {
                scale += Abs(a[i][k]);
            }

            if (scale) {
                for (k = l; k < n; k++) {
                    a[i][k] /= scale;
                    s += a[i][k] * a[i][k];
                }

                f = a[i][l];
                g = -Sign(sqrt(s), f);
                h = f * g - s;
                a[i][l] = f - g;

                for (k = l; k < n; k++) {
                    rv1[k] = a[i][k] / h;
                }

                if (i != mm1) {
                    for (j = l; j < m; j++) {
                        for (s = 0.0, k = l; k < n; k++) {
                            s += a[j][k] * a[i][k];
                        }

                        for (k = l; k < n; k++) {
                            a[j][k] += s * rv1[k];
                        }
                    }
                }

                for (k = l; k < n; k++) {
                    a[i][k] *= scale;
                }
            }
        }

        anorm = Max(anorm, (Abs(w[i]) + Abs(rv1[i])));
    }

    /* Accumulation of right-hand transformations */
    for (i = n - 1; i >= 0; i--) {
        if (i < nm1) {
            if (g) {
                /* double division to avoid possible underflow */
                for (j = l; j < n; j++) {
                    v[j][i] = (a[i][j] / a[i][l]) / g;
                }

                for (j = l; j < n; j++) {
                    for (s = 0.0, k = l; k < n; k++) {
                        s += a[i][k] * v[k][j];
                    }

                    for (k = l; k < n; k++) {
                        v[k][j] += s * v[k][i];
                    }
                }
            }

            for (j = l; j < n; j++) {
                v[i][j] = v[j][i] = 0.0;
            }
        }

        v[i][i] = 1.0;
        g = rv1[i];
        l = i;
    }

    /* Accumulation of left-hand transformations */
    for (i = n - 1; i >= 0; i--) {
        l = i + 1;
        g = w[i];

        if (i < nm1)
            for (j = l; j < n; j++) {
                a[i][j] = 0.0;
            }

        if (g) {
            g = 1.0 / g;

            if (i != nm1) {
                for (j = l; j < n; j++) {
                    for (s = 0.0, k = l; k < m; k++) {
                        s += a[k][i] * a[k][j];
                    }

                    f = (s / a[i][i]) * g;

                    for (k = i; k < m; k++) {
                        a[k][j] += f * a[k][i];
                    }
                }
            }

            for (j = i; j < m; j++) {
                a[j][i] *= g;
            }
        } else
            for (j = i; j < m; j++) {
                a[j][i] = 0.0;
            }

        ++a[i][i];
    }

    /* diagonalization of the bidigonal form */
    for (k = n - 1; k >= 0; k--) {
        /* loop over singlar values */
        for (its = 0; its < 30; its++) {
            /* loop over allowed iterations */
            flag = 1;

            for (l = k; l >= 0; l--) {
                /* test for splitting */
                nm = l - 1; /* note that rv1[l] is always zero */

                if (Abs(rv1[l]) + anorm == anorm) {
                    flag = 0;
                    break;
                }

                if (Abs(w[nm]) + anorm == anorm) {
                    break;
                }
            }

            if (flag) {
                c = 0.0; /* cancellation of rv1[l], if l>1 */
                s = 1.0;

                for (i = l; i <= k; i++) {
                    f = s * rv1[i];

                    if (Abs(f) + anorm != anorm) {
                        g = w[i];
                        h = radius(f, g);
                        w[i] = h;
                        h = 1.0 / h;
                        c = g * h;
                        s = (-f * h);

                        for (j = 0; j < m; j++) {
                            y = a[j][nm];
                            z = a[j][i];
                            a[j][nm] = y * c + z * s;
                            a[j][i] = z * c - y * s;
                        }
                    }
                }
            }

            z = w[k];

            if (l == k) {
                /* convergence */
                if (z < 0.0) {
                    w[k] = -z;

                    for (j = 0; j < n; j++) {
                        v[j][k] = (-v[j][k]);
                    }
                }

                break;
            }

            if (its == 30) {
                Print("No convergence in 30 SVDCMP iterations");
            }

            x = w[l]; /* shift from bottom 2-by-2 minor */
            nm = k - 1;
            y = w[nm];
            g = rv1[nm];
            h = rv1[k];
            f = ((y - z) * (y + z) + (g - h) * (g + h)) / (2.0 * h * y);
            g = radius(f, 1.0);
            /* next QR transformation */
            f = ((x - z) * (x + z) + h * ((y / (f + Sign(g, f))) - h)) / x;
            c = s = 1.0;

            for (j = l; j <= nm; j++) {
                i = j + 1;
                g = rv1[i];
                y = w[i];
                h = s * g;
                g = c * g;
                z = radius(f, h);
                rv1[j] = z;
                c = f / z;
                s = h / z;
                f = x * c + g * s;
                g = g * c - x * s;
                h = y * s;
                y = y * c;

                for (jj = 0; jj < n; jj++) {
                    x = v[jj][j];
                    z = v[jj][i];
                    v[jj][j] = x * c + z * s;
                    v[jj][i] = z * c - x * s;
                }

                z = radius(f, h);
                w[j] = z; /* rotation can be arbitrary id z=0 */

                if (z) {
                    z = 1.0 / z;
                    c = f * z;
                    s = h * z;
                }

                f = (c * g) + (s * y);
                x = (c * y) - (s * g);

                for (jj = 0; jj < m; jj++) {
                    y = a[jj][j];
                    z = a[jj][i];
                    a[jj][j] = y * c + z * s;
                    a[jj][i] = z * c - y * s;
                }
            }

            rv1[l] = 0.0;
            rv1[k] = f;
            w[k] = x;
        }
    }

    rfree((void*) rv1);
}
