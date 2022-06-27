#ifndef MEMORY_INTERFACE_H
#define MEMORY_INTERFACE_H

#include <stddef.h>

typedef struct mem_desc {
    struct {    
        int   (*init)(const void *params);          /* pointer to initialize function */
        void *(*m_alloc)(size_t size);              /* pointer to allocating function */
        void  (*d_alloc)(void *ptr);                /* pointer to deallocating function */
        void *(*r_alloc)(void *ptr, size_t size);   /* pointer to reallocating function */
    } vtable;
} mem_desc_t;

#endif
