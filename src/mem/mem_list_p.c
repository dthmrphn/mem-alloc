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

    /* align size to sizeof(size_t) */
    size = mem_align(size);
    
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

    /* check if new memory block doesnt overflow pool boundaries*/
    if ((void*)block + to_alloc > pool_end) {
        return NULL;
    }

    block->size = size;
    block->next = (void*)block + to_alloc;

    return block->data;
}

static void m_list_dealloc(void *ptr) {
    if (!ptr) {
        return;
    }
    /* dereference to the block holding pointer */
    mblock_t *block = (mblock_t*)(ptr - sizeof(mblock_t));

    mblock_t *prev = params_.pool;
    /* finding previous to current block */
    while (prev->next != block) {
        prev = prev->next;
    }

    prev->next = block->next;

    block->next = NULL;
    block->size = 0;
}

/**
 * @brief this function might cause UB if return value assigns to passed param ptr
 * for example void *ptr = mem_realloc(ptr, 100)
 */
static void *m_list_realloc(void *ptr, size_t size) {
    if (!ptr) {
        return m_list_alloc(size);
    }

    mblock_t *block = (mblock_t*)(ptr - sizeof(mblock_t));

    if (block->size >= size) {
        return ptr;
    }

    void *result = NULL;

    if (block->size < size) {
        result = m_list_alloc(size);
        if (!result) {
            return result;
        }
        mem_copy(result, block->data, block->size);

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
