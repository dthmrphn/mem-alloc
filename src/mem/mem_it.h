#ifndef MEMORY_INTERFACE_H
#define MEMORY_INTERFACE_H

#include <stddef.h>

/* lib-private definition of memory function descriptor */
struct mem_desc {
    struct {    
        int   (*init)(const void *params);          /* pointer to initialize function */
        void *(*m_alloc)(size_t size);              /* pointer to allocating function */
        void  (*d_alloc)(void *ptr);                /* pointer to deallocating function */
        void *(*r_alloc)(void *ptr, size_t size);   /* pointer to reallocating function */
    } vtable;
};

static inline size_t mem_align(size_t size) {
    return (size - (size % sizeof(size_t)) + sizeof(size_t));
}

#include "mem.h"

#endif
