int illegalRead(int *p) {
    return p[10];
}

void illegalWrite(int *p) {
    p[10] = 0;
}
