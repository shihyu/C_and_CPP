/*
 * add.c
 *
 *  Created on: 2013/06/23
 *      Author: shanai
 */

#include "add.h"

static int add(int, int);

int calc(int i1, int i2) {
    return add(i1, i2);
}

static int add(int i1, int i2) {
    return i1 + i2;
}
