#include <stdio.h>
#include <assert.h>
#include <string.h>

#include "array_list.h"

// データを末尾に追加し、自分自身を返す。
// サイズが足りない場合はassertエラーになる。
ArrayList *add_to_array_list(ArrayList *pThis, void *pData) {
    assert(pThis->capacity > pThis->index);
    pThis->pBuf[pThis->index++] = pData;
    return pThis;
}

// 指定されたデータを削除し、削除されたデータを返す。
// 見つからない場合はNULLが返る。
void *remove_from_array_list(ArrayList *pThis, void *pData) {
    int i;

    for (i = 0; i < pThis->index; ++i) {
        if (pThis->pBuf[i] == pData) {
            memmove(pThis->pBuf + i, pThis->pBuf + i + 1, (pThis->index - i - 1) * sizeof(void *));
            --pThis->index;
            return pData;
        }
    }

    return NULL;
}

// 指定された場所のデータを返す。
// indexの値がデータの格納されている範囲外の場合はassertエラーになる。
void *get_from_array_list(ArrayList *pThis, int index) {
    assert(0 <= index && pThis->index > index);
    return pThis->pBuf[index];
}

// 格納されているデータの個数を返す。
size_t array_list_size(ArrayList *pThis) {
    return pThis->index;
}
