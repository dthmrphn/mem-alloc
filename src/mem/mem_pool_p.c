/**
  *pool (chunk) allocator private functions and interface description
  **/

#include "mem.h"

/* count of memory pools */
#define MEM_POOL_RESOURCE_COUNT     5

/* meta of pool allocator blocks */
typedef struct memblock {
    size_t size;    /* size of allocated data block */
    uint8_t data[]; /* pointer to allocated block   */
} mblock_t;

/* holding allocator's params there */
static p_pool_t params_[MEM_POOL_RESOURCE_COUNT];
static size_t last_added = 0;

/* should return error ?*/
static int m_pool_init(const void *params) {
    if (last_added < MEM_POOL_RESOURCE_COUNT) {
        params_[last_added] = *(p_pool_t*)params;
        ++last_added;
        return 0;
    }
    return 1;
}

static p_pool_t m_pool_match(size_t size) {
    p_pool_t rv = {0, 0, 0};

    for (size_t i = 0; i < last_added; i++) {
        if (size < params_[i].size) {
            rv = params_[i];
            break;
        }
    }
    return rv;
}

static void *m_pool_alloc(size_t size) {
    p_pool_t param = m_pool_match(size);

    if (size > (param.size - sizeof(mblock_t)) || !param.pool) {
        return NULL;
    }

    void *tmp = NULL;
    void *ptr = param.pool;
    for (size_t i = 0; i < param.count; ++i) {
        /* storing block in chunk */
        mblock_t *block = (mblock_t*)ptr; 
                
        if (block->size == 0) {
            block->size = size;
            tmp = block->data;
            break;
        } 

        /* moving to next chunk */
        ptr = ptr + param.size;
    }

    return tmp;
}

static void m_pool_dealloc(void *ptr) {
    if (!ptr) return;

    mblock_t *block = (mblock_t*)(ptr - sizeof(size_t));
    block->size = 0;
}

static void *m_pool_realloc(void *ptr, size_t size) {
    (void)ptr;
    return m_pool_alloc(size);
}

const mem_desc_t m_pool_desc = {
    .vtable = {
        .init = m_pool_init,
        .m_alloc = m_pool_alloc,
        .d_alloc = m_pool_dealloc,
        .r_alloc = m_pool_realloc
    }
};
