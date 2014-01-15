#include <stdio.h>
#include <stdlib.h>

#include "conservativegc.h"

void test() {
    int i;
    void* addr;

    for (i = 0; i < 4096; ++i) {
        addr = malloc(1024);
        printf("%d: %p\n", i, addr);
    }
}

int main(int argc, char** argv) {
    gc_init(&argc);
    setvbuf(stdout, NULL, _IONBF, 0);
    test();
    gc_cleanup();
    return EXIT_SUCCESS;
}

