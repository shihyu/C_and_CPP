/*======================================================
//º¯ÊıÃû£ºTminv
//¹¦ÄÜÃèÊö£ºToeplitz¾ØÕó¿ìËÙÇóÄæ
//ÊäÈë²ÎÊı£ºt1 Ë«¾«¶ÈÊµĞÍÒ»Î¬Êı×éµÄÖ¸Õë¬
            Êı×éÖĞ´æ·Ån½×TĞÍ¾ØÕóµÚÒ»¸öÔªËØ¼°ÉÏÈı½ÇÔªËØ
            t2 Ë«¾«¶ÈÊµĞÍÒ»Î¬Êı×éµÄÖ¸Õë¬
            ÆäÖĞºón-1¸öÔªËØ´æ·Ån½×TĞÍ¾ØÕóÖĞµÄÏÂÈı½ÇÔªËØ
            n ¾ØÕó½×Êı
            mat ·µ»ØµÄÄæ¾ØÕó´æ·ÅÎ»ÖÃ
            eps ¾«¶ÈÒªÇó£¬¾ø¶ÔÖµĞ¡ÓÚ´ËÊıµÄÖµÈÏÎªÊÇ0
//·µ»ØÖµ£ºÕûĞÍ¡£ÔËĞĞ³É¹¦Ôò·µ»Ø1,Ê§°ÜÔò·µ»Ø0
=========================================================*/
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

int Tminv(t1, t2, n, mat, eps)
double* t1, *t2;
int n;
double* mat;
double eps;
{
    int i, j, k, l;
    double a, tmp, *c, *r, *p;

    c = (double*)malloc(n * sizeof(double));   /* ÎªÁÙÊ±±äÁ¿·ÖÅä¿Õ¼ä*/
    r = (double*)malloc(n * sizeof(double));
    p = (double*)malloc(n * sizeof(double));

    if (fabs(t1[0]) < eps) {                   /* ¼ì²éÊ×ÏîÊÇ·ñÎª0*/
        free(c);                                 /* ÈôÊ×ÏîÎª0£¬ÔòÊÍ·Å¿Õ¼ä²¢ÍË³ö*/
        free(r);
        free(p);
        printf("Fail to invert\n");
        return (0);
    }

    a = t1[0];                                /* ¼ÆËã³õÖµ*/
    c[0] = t2[1] / t1[0];
    r[0] = t1[1] / t1[0];

    for (k = 0; k < n - 2; k++) {             /* k´Ó0µ½n-3×öÈçÏÂµÄÑ­»·*/
        tmp = 0.0;

        for (j = 1; j < k + 2; j++) {         /* ÇóµÚÒ»¸öÀÛ¼ÓºÍ*/
            tmp = tmp + c[k + 1 - j] * t2[j];
        }

        tmp = (tmp - t2[k + 2]) / a;

        for (i = 0; i < k + 1; i++) {     /* ÏÈ´æ·ÅÔÚpÖĞ£¬ÒòÎªc[i]µÄÔ­Öµ»¹ÒªÊ¹ÓÃ*/
            p[i] = c[i] + tmp * r[k - i];
        }

        c[k + 1] = -tmp;                  /* ĞÂÇó³öc[k+1]µÄÖµ*/

        tmp = 0.0;

        for (j = 1; j < k + 2; j++) {     /* µÚ¶ş¸öÀÛ¼ÓºÍ*/
            tmp = tmp + r[k + 1 - j] * t1[j];
        }

        tmp = (tmp - t1[k + 2]) / a;

        for (i = 0; i < k + 1; i++) {
            r[i] = r[i] + tmp * c[k - i]; /* ¸üĞÂr[i]µÄÖµ*/
            c[k - i] = p[k - i];          /* c[k-i]µÄÖµ²»ÔÙÊ¹ÓÃ£¬ÓÃpÖĞµÄÊı¾İ¸üĞÂ*/
        }

        r[k + 1] = -tmp;                  /* ĞÂÇó³ör[k+i]µÄÖµ*/

        a = 0.0;

        for (j = 1; j < k + 3; j++) {     /* ¸üĞÂaµÄÖµ*/
            a = a + t1[j] * c[j - 1];
        }

        a = t1[0] - a;

        if (fabs(a) < eps) {              /* Èôa¹ıĞ¡£¬ÔòÍË³öº¯Êı¡£ÇóÄæ¹ı³Ì²»ÄÜ¼ÌĞø*/
            free(c);                      /* ÊÍ·Å¿Õ¼ä*/
            free(r);
            free(p);
            printf("Fail to invert\n");
            return (0);
        }
    }

    mat[0] = 1.0 / a;                    /* ÀûÓÃÇóµÃµÄr,c,a¹¹ÔìÄæ¾ØÕó*/

    for (i = 0; i < n - 1; i++) {
        k = i + 1;
        mat[k] = -r[i] / a;              /* Äæ¾ØÕóµÄµÚÒ»ĞĞ*/
        mat[k * n] = -c[i] / a;          /* Äæ¾ØÕóµÄµÚÒ»ÁĞ*/
    }

    for (i = 0; i < n - 1; i++)          /* Äæ¾ØÕóµÄÆäËûÔªËØ*/
        for (j = 0; j < n - 1; j++) {
            l = (i + 1) * n + j + 1;
            k = i * n + j;
            mat[l] = mat[k] + (c[i] * r[j] - r[n - 2 - i] * c[n - 2 - j]) / a;
        }

    free(c);                            /* ÊÍ·Å¿Õ¼ä*/
    free(r);
    free(p);
    return (1);
}
