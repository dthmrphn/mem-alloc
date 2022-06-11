#ifndef MEMORY_INTERFACE_H
#define MEMORY_INTERFACE_H

#include <stddef.h>

typedef struct mem_desc {
    struct {
        int   (*init)(const void* params);
        void* (*allocate)(size_t size);
        void  (*deallocate)(void* ptr);
    } vtable;
} mem_desc_t;

int   mem_init(const void* desc, const void* params);
void* mem_alloc(size_t size);
void  mem_free(void* ptr);


#endif
