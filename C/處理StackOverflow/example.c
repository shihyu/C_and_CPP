#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
#include <signal.h>

sigjmp_buf stack_overflow_guard;

char alter_stack[4096];

void sigsegv_handler(int sig) {
    if (sig == SIGSEGV) {
        /* Jump to catch block */
        siglongjmp(stack_overflow_guard, sig);
    }
}

void install_sigsegv_handler() {
    /* Prepare alternating stack */
    stack_t stk;
    stk.ss_sp = alter_stack;
    stk.ss_size = sizeof(alter_stack);
    stk.ss_flags = 0;

    if (sigaltstack(&stk, NULL) == -1) {
        fprintf(stderr, "ERROR: Unable to setup alternative stack.\n");
        exit(EXIT_FAILURE);
    }

    /* Register SIGSEGV handler */
    struct sigaction act;
    act.sa_handler = &sigsegv_handler;
    sigfillset(&act.sa_mask);
    act.sa_flags |= SA_ONSTACK;

    if (sigaction(SIGSEGV, &act, NULL) == -1) {
        fprintf(stderr, "ERROR: Unable to instal signal handler.\n");
        exit(EXIT_FAILURE);
    }
}

int trigger_stack_overflow(int a, int b, int c, int d, int e) {
    return trigger_stack_overflow(a + 1, b + 1, c + 1, d + 1, e + 1) *
           trigger_stack_overflow(a - 1, b - 1, c - 1, d - 1, e - 1);
}

int main() {
    install_sigsegv_handler();

    if (sigsetjmp(stack_overflow_guard, 0) == 0) {
        printf("normal path, got: %d\n",
               trigger_stack_overflow(0, 0, 0, 0, 0));
    } else {
        printf("stack overflow\n");
    }

    return EXIT_SUCCESS;
}
