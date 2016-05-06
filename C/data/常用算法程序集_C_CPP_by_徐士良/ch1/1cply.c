
void cply(ar, ai, n, x, y, u, v)
int n;
double x, y, ar[], ai[], *u, *v;
{
    int i;
    double p, q, s, t;
    void cmul(double, double, double, double, double*, double*);
    s = ar[n - 1];
    t = ai[n - 1];

    for (i = n - 2; i >= 0; i--) {
        cmul(s, t, x, y, &p, &q);
        s = p + ar[i];
        t = q + ai[i];
    }

    *u = s;
    *v = t;
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

