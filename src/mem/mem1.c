/**
 * pool (chunk) allocator
 * */

#include "include/mem.h"

#define BLOCK_SIZE 200
#define BLOCK_COUNT 200

typedef struct memblock {
    size_t al_size;
    size_t using;
    uint8_t data[];
} mblock_t;

static void* pool_;
static size_t count_;
static size_t size_;

static int mmalloc_init_(const void* pool, size_t count, size_t size) {
    pool_ = pool;
    count_ = count;
    size_ = size;
}

static void* mmalloc_(size_t size) {
    if (size > size_ || !pool_) {
        return NULL;
    }

    void* tmp = NULL;
    void* ptr = pool_;
    for (size_t i = 0; i < count_; ++i) {
        /* storing block in chunk */
        mblock_t* block = (mblock_t*)ptr; 
                
        if (block->using == 0) {
            block->al_size = size;
            block->using = 1;
            tmp = block->data;
            break;
        } 

        /* moving to next chunk */
        ptr = ptr + size_;
    }

    return tmp;
}

static void mfree_(void* ptr) {
    if (!ptr) return;

    mblock_t* block = (mblock_t*)(ptr - 2 * sizeof(size_t));
    block->al_size = 0;
    block->using = 0;
}

void* mmalloc(size_t size) {
    return mmalloc_(size);
}

void mfree(void* ptr) {
    return mfree_(ptr);
}

int mmalloc_init(const void* resourse, const void* params) {
    pparam_t* param = (pparam_t*)params;
    return mmalloc_init_(resourse, param->count, param->size);
}