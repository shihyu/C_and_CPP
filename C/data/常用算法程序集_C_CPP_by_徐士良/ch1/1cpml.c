
void cpml(pr, pi, m, qr, qi, n, sr, si, k)
int m, n, k;
double pr[], pi[], qr[], qi[], sr[], si[];
{
    int i, j;
    double a, b, c, d, u, v;
    void cmul(double, double, double, double, double*, double*);

    for (i = 0; i <= k - 1; i++) {
        sr[i] = 0.0;
        si[i] = 0.0;
    }

    for (i = 0; i <= m - 1; i++)
        for (j = 0; j <= n - 1; j++) {
            a = pr[i];
            b = pi[i];
            c = qr[j];
            d = qi[j];
            cmul(a, b, c, d, &u, &v);
            sr[i + j] = sr[i + j] + u;
            si[i + j] = si[i + j] + v;
        }

    return;
}

static void cmul(a, b, c, d, e, f)
double a, b, c, d, *e, *f;
{
    double p, q, s;
    p = a * c;
    q = b * d;
    s = (a + b) * (c + d);
    *e = p - q;
    *f = s - p - q;
    return;
}

