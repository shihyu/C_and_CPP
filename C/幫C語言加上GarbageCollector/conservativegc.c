#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/mman.h>

#include "conservativegc.h"


#define FLOOR_ALIGN_TO_WORD(X) \
    (((uintptr_t)(X)) / sizeof(void *) * sizeof(void *))

#define CEIL_ALIGN_TO_WORD(X) \
    (((uintptr_t)(X) + sizeof(void *) - 1) / sizeof(void *) * sizeof(void *))


enum {
    ALLOC_STATUS_UNKNOWN,
    ALLOC_STATUS_TOUCHED,
    ALLOC_STATUS_REFERRED,
    ALLOC_STATUS_DEALLOCATED,
};


typedef struct alloc_record_ {
    char* addr;
    size_t size;
    unsigned int status;
} alloc_record;


static char* heap_begin = NULL;
static char* heap_free = NULL;
static char* heap_end = NULL;

static size_t alloc_record_count = 0;

static void** stack_top = NULL;


/* Find the allocation record from the list. */
static alloc_record* find_alloc_record(char* addr) {
    alloc_record* begin = (alloc_record*)heap_end - alloc_record_count;
    alloc_record* end = (alloc_record*)heap_end;

    if (begin >= end) {
        return NULL;
    }

    /* Note: The alloc_record pointed by begin has greater addr value.  The
       alloc_record between [begin, end) is descending. */
    alloc_record* last = end - 1;
    char* highest_addr = begin->addr + begin->size;
    char* lowest_addr = last->addr;

    if (!(addr >= lowest_addr && addr < highest_addr)) {
        /* Address not in the managed range. */
        return NULL;
    }

    /* Binary search for the address */
    while (end - begin > 1) {
        alloc_record* mid = begin + (end - begin) / 2;

        if (addr >= mid->addr) {
            if (addr < mid->addr + mid->size) {
                return mid;
            } else {
                end = mid;
            }
        } else {
            begin = mid;
        }
    }

    assert(addr >= begin->addr && addr < begin->addr + begin->size);
    return begin;
}


/* Insert a new record at the end of the list. */
static void insert_alloc_record(char* addr, size_t size) {
    alloc_record_count++;
    alloc_record* record = (alloc_record*)heap_end - alloc_record_count;
    record->addr = addr;
    record->size = size;
    record->status = ALLOC_STATUS_REFERRED;
}


/* Check the availability of the free space */
static int is_free_space_avail(size_t size) {
    return size + sizeof(alloc_record) <=
           heap_end - heap_free - sizeof(alloc_record) * alloc_record_count;
}


/* Initialize the internal data structure of the garbage collector */
void gc_init(int* argc_ptr) {
    /* We assume that argc is the variable in the stack having the highest
       address. */
    stack_top = (void**)CEIL_ALIGN_TO_WORD(argc_ptr);
    /* Allocate the heap using mmap. */
    heap_begin = (char*)mmap(0, GC_HEAP_SIZE, PROT_READ | PROT_WRITE,
                             MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (!heap_begin || heap_begin == MAP_FAILED) {
        fprintf(stderr, "Unable to allocate the heap (size=%lu).\n",
                (unsigned long)GC_HEAP_SIZE);
        exit(EXIT_FAILURE);
    }

    heap_free = heap_begin;
    heap_end = heap_begin + GC_HEAP_SIZE;
}


/* Recycle and allocate the deallocated address. */
static void* allocate_deallocated_block(size_t size) {
    alloc_record* records = (alloc_record*)heap_end - alloc_record_count;
    /* Find the feasible block using the first-fit algorithm. */
    size_t i, j;

    for (j = alloc_record_count, i = j - 1; j > 0; --i, --j) {
        if (records[i].status == ALLOC_STATUS_DEALLOCATED &&
                records[i].size >= size) {
            records[i].status = ALLOC_STATUS_REFERRED;
            return records[i].addr;
        }
    }

    return NULL;
}


/* Allocate a block with given bytes. */
void* gc_malloc(size_t size) {
    /* Make sure that all of returned address is aligned to WORD */
    size = CEIL_ALIGN_TO_WORD(size);

    /* Try to allocate if free space available */
    if (is_free_space_avail(size)) {
        char* result = heap_free;
        heap_free += size;
        insert_alloc_record(result, size);
        return result;
    }

    /* Try to allocate from deallocated address. */
    void* result = allocate_deallocated_block(size);

    if (result) {
        return result;
    }

    /* Try to collect garbage and retry. */
    while (gc_cleanup()) {
        void* result = allocate_deallocated_block(size);

        if (result) {
            return result;
        }
    }

    return NULL;
}


/* Deallocate and wipe the allocated block. */
static void deallocate(alloc_record* record) {
    assert(record != NULL);
    /* Mark this block as deallocated */
    record->status = ALLOC_STATUS_DEALLOCATED;
    /* Wipe the memory block for cleaning the possible pointer address */
    memset(record->addr, '\0', record->size);
}


/* Deallocate the given address and wipe the pointer. */
void gc_free_(void** addr_ptr) {
    alloc_record* record = find_alloc_record(*addr_ptr);

    if (!record) {
        fprintf(stderr, "Memory corrupted. given addr: %p\n", *addr_ptr);
        return;
    }

    deallocate(record);
    *addr_ptr = NULL;
}


/* Scan for address between [begin, end) */
static void scan_and_touch(void* begin_, void* end_) {
    void** begin = (void**)FLOOR_ALIGN_TO_WORD(begin_);
    void** end = (void**)FLOOR_ALIGN_TO_WORD(end_);

    for (; begin < end; ++begin) {
        char* addr = (char*)*begin;

        if (addr >= heap_begin && addr < heap_free) {
            alloc_record* record = find_alloc_record(addr);

            if (record && record->status == ALLOC_STATUS_UNKNOWN) {
                record->status = ALLOC_STATUS_TOUCHED;
            }
        }
    }
}


/* Scan the touched objects */
static void scan_touched_objects() {
    alloc_record* records = (alloc_record*)heap_end - alloc_record_count;
    size_t count, i;

    do {
        count = 0;

        for (i = 0; i < alloc_record_count; ++i) {
            if (records[i].status != ALLOC_STATUS_TOUCHED) {
                /* Not in touched state, skip it. */
                continue;
            }

            /* Mark as referred so that it wont be touched again. */
            records[i].status = ALLOC_STATUS_REFERRED;
            /* Scan this object */
            scan_and_touch((void**)(records[i].addr),
                           (void**)(records[i].addr + records[i].size));
            count++;
        }
    } while (count > 0); /* Loop until no TOUCHED allocation is proceed. */
}


/* Garbage collection and deallocate unused memory. */
size_t gc_cleanup_(int stack_indicator) {
    alloc_record* records = (alloc_record*)heap_end - alloc_record_count;
    size_t i, j;

    /* Mark alloc record as UNKNOWN if it is not deallocated. */
    for (i = 0; i < alloc_record_count; ++i) {
        if (records[i].status != ALLOC_STATUS_DEALLOCATED) {
            records[i].status = ALLOC_STATUS_UNKNOWN;
        }
    }

    /* Scan the stack */
    void** stack_bottom = (void**)CEIL_ALIGN_TO_WORD(&stack_indicator);
    assert(stack_top != NULL);
    assert(stack_bottom <= stack_top);
    scan_and_touch(stack_bottom, (void**)stack_top);
    /* Scan the heap */
    scan_touched_objects();
    /* Deallocate and reset the status */
    static unsigned int gc_count = 0;
    static char const sep[] =
        "-------------------------------------------------------";
    fprintf(stderr, "%s\n", sep);
    fprintf(stderr, "GARBAGE COLLECTION ROUND #%u\n", ++gc_count);
    size_t deallocated_count = 0;

    for (j = alloc_record_count, i = j - 1; j > 0; --i, --j) {
        if (records[i].status == ALLOC_STATUS_UNKNOWN) {
            fprintf(stderr, "  Reclaim [addr: %p, size: %lu]\n",
                    records[i].addr, (unsigned long)records[i].size);
            deallocate(&records[i]);
            ++deallocated_count;
        }
    }

    fprintf(stderr, "%s\n\n", sep);
    return deallocated_count;
}

