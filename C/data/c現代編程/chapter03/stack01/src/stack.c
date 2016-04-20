#include <stdbool.h>
#include "stack.h"

int buf[16];
int top = 0;

bool isStackFull(void) {
  return top == sizeof(buf) / sizeof(int);
}

bool isStackEmpty(void) {
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
