
#include "stdio.h"
#include "15hshl.c"
main()
{
    int i, j;
    static char* p[18] = {"main", "gou", "zhao", "lin", "wang",
                          "zhang", "li", "zhen", "ma", "sub", "china", "beijin",
                          "liang", "juan", "yan", "teacher", "student", "qssort"
                         };
    printf("\n");

    for (j = 0; j <= 1; j++) {
        for (i = 0; i <= 8; i++) {
            printf("%s , ", p[9 * j + i]);
        }

        printf("\n");
    }

    hshl(p, 18, 0, 17);
    printf("\n");

    for (j = 0; j <= 1; j++) {
        for (i = 0; i <= 8; i++) {
            printf("%s , ", p[9 * j + i]);
        }

        printf("\n");
    }

    printf("\n");
}

