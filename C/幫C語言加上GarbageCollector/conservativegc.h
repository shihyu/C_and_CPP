#if !defined(CONSERVATIVEGC_H)
#define CONSERVATIVEGC_H

#include <stddef.h>

#define GC_HEAP_SIZE (4 * 1024 * 1024)

extern void gc_init(int* argc_addr);

extern void* gc_malloc(size_t i);
extern void gc_free_(void** addr_ptr);

extern size_t gc_cleanup_(int EVERY_INTEGER_IS_OK);
#define gc_cleanup() gc_cleanup_(0)

#if defined(malloc)
#undef malloc
#endif

#define malloc(SIZE) gc_malloc(SIZE)

#if defined(free)
#undef free
#endif

#define free(ADDR) gc_free_(&(ADDR))

#endif /* CONSERVATIVEGC_H */
