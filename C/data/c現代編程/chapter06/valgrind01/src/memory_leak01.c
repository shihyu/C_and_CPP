#include <stdlib.h>

static int *range(int from, int to);

void memoryLeak() {
    int *p = range(3, 5);
}

static int *range(int from, int to) {
    int *p = (int *)malloc(sizeof(int) * (to - from));
    for (int i = from; i < to; ++i) {
        p[i - from] = i;
    }
    return p;
}
