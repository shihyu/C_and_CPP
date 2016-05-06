
int csech(p, k, m, a, b)
STRU p[];
char  a, b;
int k, m;
{
    int i;
    i = k;

    while ((i <= m) && ((p[i].KEY < a) || (p[i].KEY > b))) {
        i = i + 1;
    }

    if (i > m) {
        return (-1);
    }

    return (i);
}

