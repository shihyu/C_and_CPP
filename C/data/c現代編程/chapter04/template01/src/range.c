#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int range(const char *pFname) {
    FILE *fp = fopen(pFname, "r");
    if (fp == NULL) return -1;

    int min = INT_MAX;
    int max = INT_MIN;
    char buf[256];

    while ((fgets(buf, sizeof(buf), fp)) != NULL) {
        buf[sizeof(buf) - 1] = '\0';
        int value = atoi(buf);
        min = min > value ? value : min;
        max = max < value ? value : max;
    }

    fclose(fp);
    return max - min;
}
