#include <stdio.h>

#if 1
enum _MIKEY_ {
    Valid = 0,
    Pass,
    Fail
};

int DecoderH264(enum _MIKEY_ x, int key_content, int key_value) {
#else
typedef enum _MIKEY_ {
    Valid = 0,
    Pass,
    Fail
} en_MIKEY;

int DecoderH264(en_MIKEY x, int key_content, int key_value) {
#endif
    printf("%d\n", x);
    return 0;
}

int main(int argc, char* argv[]) {
    DecoderH264(Pass, 0, 0);
    return 0;
}
