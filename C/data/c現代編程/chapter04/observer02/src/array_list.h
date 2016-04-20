#ifndef _ARRAY_LIST_H_
#define _ARRAY_LIST_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ArrayList {
    const int capacity;
    void ** const pBuf;
    size_t index;

    struct ArrayList *(* const add)(struct ArrayList *pThis, void *pData);
    void *(* const remove)(struct ArrayList *pThis, void *pData);
    void *(* const get)(struct ArrayList *pThis, int index);
    size_t (* const size)(struct ArrayList *pThis);
} ArrayList;

ArrayList *add_to_array_list(ArrayList *pThis, void *pData);
void *remove_from_array_list(ArrayList *pThis, void *pData);
void *get_from_array_list(ArrayList *pThis, int index);
size_t array_list_size(ArrayList *pThis);

#define new_array_list(array) \
    {sizeof(array) / sizeof(void *), array, \
     0, add_to_array_list, remove_from_array_list, get_from_array_list, array_list_size}

#ifdef __cplusplus
}
#endif

#endif
