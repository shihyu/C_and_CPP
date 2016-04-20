#include <stdio.h>

#include "uninitialized01.h"

static void print(int i) {
    if (i == 0)
        printf("zero\n");
}

void uninitialized() {
    int i;
    print(i);
}
