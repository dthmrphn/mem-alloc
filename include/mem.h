#include <stddef.h>
#include <stdint.h>

typedef struct poolparam {
    size_t size;    /* size of chunk */
    size_t count;   /* count of chunks */
} pparam_t;

void* mmalloc(size_t size);
int   mmalloc_init(const void* resourse, const void* params);
void  mfree(void* ptr);