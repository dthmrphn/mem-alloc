#include <stdint.h>
#include <stdio.h>


typedef struct memblock {
    size_t al_size;
    size_t using;
    void* data;
} mblock_t;

typedef struct linkblock {
    mblock_t* this;
    lblock_t* next;
} lblock_t;

static void * pool_ = NULL;
static size_t pool_size_ = 0;

void mmalloc_init(void* pool, size_t size) {
    pool_ = pool;
    pool_size_ = size;
}

static void* mmalloc_(lblock_t* block, size_t size) {
    if (!pool_) {
        return NULL;
    }

    if (size > pool_size_) {
        return  NULL;
    }

    if (!block) {
        return NULL;
    }

    if (!block->this) {
        mblock_t* tmp = pool_;
        void* res = tmp->data;
        tmp->al_size = size;
        tmp->using = 1;

        block->this = tmp;
        block->next = pool_ + sizeof(mblock_t);

        return res;
    }

    lblock_t* tmp = block;
    while (tmp->next) {
        tmp = block->next;
    }

    size_t diff = 
}

