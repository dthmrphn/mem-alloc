#ifndef MEM_H
#define MEM_H

#include <stddef.h>
#include <stdint.h>

#include "mem_it.h"

/* pool allocator params */
typedef struct poolparam {
    void*  pool;    /* address of pool */
    size_t size;    /* size of chunk   */
    size_t count;   /* count of chunks */
} p_pool_t;

int   mem_init(const void* desc, const void* params);
void* mem_alloc(size_t size);
void  mem_free(void* ptr);

extern const mem_desc_t m_pool_desc;

#endif
