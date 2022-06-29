/**
  *linked list allocator private functions and interface description
  **/

#include "mem_it.h"

/* meta of linked list allocator blocks */
typedef struct memblock {
    struct memblock *next;  /* next block stored in pool    */
    size_t size;            /* size of allocated data block */
    uint8_t data[];         /* pointer to allocated block   */
} mblock_t;

static p_pool_t params_;

static int m_list_init(const void *params) {
    params_ = *(p_pool_t*)params;

    /* storing root link into pool */
    mblock_t *root = params_.pool;
    root->size = 0;
    root->next = (void*)root + sizeof(mblock_t);

    return 0;
}

static void *m_list_alloc(size_t size) {
    if (!params_.pool) {
        return NULL;
    }
    const void *pool_end = (void*)(params_.pool + params_.size - 1);
    mblock_t *block = (mblock_t*)(params_.pool);
    size_t to_alloc = size + sizeof(mblock_t);

    while (block->next && (void*)block < pool_end) {
        /* check if new block could be linked between allocated blocks */
        if (((void*)block->data + block->size + to_alloc) < (void*)block->next) {
            /* inserting new block */
            mblock_t *tmp = (void*)block->data + block->size;
            tmp->next = block->next;
            block->next = tmp;
            tmp->size = size;

            return tmp->data;
        }

        block = block->next;
    }

    block->size = size;
    block->next = (void*)block + to_alloc;


    return block->data;
}

static void m_list_dealloc(void *ptr) {
    /* dereference to the block holding pointer */
    mblock_t *block = (void*)(ptr - sizeof(mblock_t));

    mblock_t *prev = params_.pool;
    /* finding previous to current block */
    while (prev->next != block) {
        prev = prev->next;
    }

    prev->next = block->next;

    block->next = NULL;
    block->size = 0;
}

static void *m_list_realloc(void *ptr, size_t size) {
    if (!ptr) {
        return m_list_alloc(size);
    }

    mblock_t *block = (void*)(ptr - sizeof(mblock_t));

    void *result = NULL;

    if (block->size < size) {
        /* 1. alloc */
        result = m_list_alloc(size);
        if (!result) {
            return result;
        }
        /* 2. copy */
        mem_copy(result, block->data, block->size);
        /* 3. free */
        m_list_dealloc(ptr);
    }

    return result;
}

const mem_desc_t m_list_desc = {
    .vtable = {
        .init = m_list_init,
        .m_alloc = m_list_alloc,
        .d_alloc = m_list_dealloc,
        .r_alloc = m_list_realloc
    }
};
