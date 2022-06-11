/**
 * pool (chunk) allocator private functions and interface description
 * */

#include "mem.h"

/* meta of pool allocator blocks*/
typedef struct memblock {
    size_t size;    /* size of allocated data block */
    uint8_t data[]; /* pointer to allocated block   */
} mblock_t;

/* holding allocator's params there */
static p_pool_t params_;

/* should return error ?*/
static int m_pool_init(const void* params) {
    params_ = *(p_pool_t*)params;
    return 0;
}

static void* m_pool_alloc(size_t size) {
    if (size > (params_.size - sizeof(mblock_t)) || !params_.pool) {
        return NULL;
    }

    void* tmp = NULL;
    void* ptr = params_.pool;
    for (size_t i = 0; i < params_.count; ++i) {
        /* storing block in chunk */
        mblock_t* block = (mblock_t*)ptr; 
                
        if (block->size == 0) {
            block->size = size;
            tmp = block->data;
            break;
        } 

        /* moving to next chunk */
        ptr = ptr + params_.size;
    }

    return tmp;
}

static void m_pool_dealloc(void* ptr) {
    if (!ptr) return;

    mblock_t* block = (mblock_t*)(ptr - sizeof(size_t));
    block->size = 0;
}

const mem_desc_t m_pool_desc = {
    .vtable = {
        .init = m_pool_init,
        .allocate = m_pool_alloc,
        .deallocate = m_pool_dealloc
    }
};
