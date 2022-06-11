#include "mem.h"

#include <stdio.h>

#define BLOCK_COUNT 50
#define BLOCK_SIZE  100

static uint8_t pool[BLOCK_COUNT][BLOCK_SIZE];
p_pool_t pool_param = {
    .pool = pool,
    .count = BLOCK_COUNT,
    .size = BLOCK_SIZE
};

int main() {
    mem_init(&m_pool_desc, &pool_param);

    void* ptr1 = mem_alloc(10);
    void* ptr2 = mem_alloc(20);
    void* ptr3 = mem_alloc(30);
    void* ptr4 = mem_alloc(100);

    mem_free(ptr1);
    mem_free(ptr2);
    mem_free(ptr3);
    mem_free(ptr4);

    return 0;
}
