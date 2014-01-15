#include <stdio.h>
#include <stdlib.h>

/* libffi 的 header */
#include <ffi.h>

/* 一些亂七八糟的函式 */
int func0() {
    printf("%s()\n", __func__);
    return 0;
}

int func1(int p0) {
    printf("%s(%d)\n", __func__, p0);
    return p0;
}

int func2(int p0, int p1) {
    printf("%s(%d, %d)\n", __func__, p0, p1);
    return p0 + p1;
}

/* 函式查詢表。也可以使用 hash table、binary tree 來實作，
   不過作為一個簡單的範例直接使用 array 就好了。 */
void* func_table[] = {
    (void*)func0, (void*)func1, (void*)func2,
};

int main(int argc, char** argv) {
    int i;

    /* 決定我們要使用哪一個函式 */
    if (argc < 2) {
        fprintf(stderr, "USAGE: %s parameter-count\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int parameter_count = atoi(argv[1]);

    if (parameter_count > 2) {
        fprintf(stderr, "WARNING: Parameter count is greater than 2.\n");
        parameter_count = 2;
    }

    /* 讀取函式的參數 */
    int values[2] = { 0 , 0 };

    for (i = 0; i < parameter_count; ++i) {
        if (scanf("%d", &values[i]) != 1) {
            static char const* const postfix[] = {
                "th", "st", "nd", "rd", "th",
                "th", "th", "th", "th", "th"
            };
            fprintf(stderr, "Unable to read %d%s parameter\n",
                    i + 1, postfix[(i + 1) % 10]);
            exit(EXIT_FAILURE);
        }
    }

    /* 使用 libffi 呼叫指定的函式 */
    ffi_cif cif;
    ffi_type* args[] = { &ffi_type_sint, &ffi_type_sint };
    void* ptr_values[] = { &values[0], &values[1] };

    /* 準備 ffi 所需的資料結構 */
    if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, parameter_count,
                     &ffi_type_sint, args) == FFI_OK) {
        int sum = 0;
        /* 執行函式呼叫 */
        ffi_call(&cif, func_table[parameter_count], &sum, ptr_values);
        printf("return value: %d\n", sum);
    } else {
        fprintf(stderr, "Unable to initialize FFI structure.\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
