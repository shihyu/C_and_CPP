#include <string.h>
#include <assert.h>

#include "strcpy01.h"

char *dropTop(char *p) {
    assert(*p != 0);
    return strcpy(p, p + 1);
}
