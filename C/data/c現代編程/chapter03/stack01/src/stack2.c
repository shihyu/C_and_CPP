#include <stdbool.h>

static int buf[16];
static int top = 0;

static bool isStackFull(void) {
  return top == sizeof(buf) / sizeof(int);
}
