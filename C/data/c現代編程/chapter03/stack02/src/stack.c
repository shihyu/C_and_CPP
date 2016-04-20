#include <stdbool.h>
#include "stack.h"

static int buf[16];
static int top = 0;

static bool isStackFull(void) {
  return top == sizeof(buf) / sizeof(int);
}

static bool isStackEmpty(void) {
  return top == 0;
}

// true: 成功, false: 失敗
bool push(int val) {
    if (isStackFull()) return false;
    buf[top++] = val;
    return true;
}

// true: 成功, false: 失敗
bool pop(int *pRet) {
    if (isStackEmpty()) return false;
    *pRet = buf[--top];
    return true;
}
