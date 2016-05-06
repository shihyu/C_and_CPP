
#include "stdio.h"
#include "15hshl.c"
#include "16hbsh.c"
main()
{
    int i, j, m0, *m;
    char aa[8], bb[8], *a = aa, *b = bb;
    static char* p[18] = {"main", "gou", "zhao", "lin", "wang",
                          "zhang", "li", "zhen", "ma", "sub", "china",
                          "beijin", "liang", "juan",
                          "yan", "teacher", "student", "qssort"
                         };
    m = &m0;
    hshl(p, 18, 0, 17);
    printf("\n");

    for (i = 0; i <= 1; i++) {
        for (j = 0; j <= 8; j++) {
            printf("%s  ", p[9 * i + j]);
        }

        printf("\n");
    }

    printf("\n");
    a = "l";
    b = "r";
    i = hbsh(p, 18, a, b, m);
    printf("m=%d\n", m0);
    printf("i=%d\n", i);

    for (j = i; j <= i + m0 - 1; j++) {
        printf("p(%d)=%s\n", j, p[j]);
    }

    printf("\n");
}

