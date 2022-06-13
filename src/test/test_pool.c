#include "mem.h"
#include "tests.h"

#include <stddef.h>

#define BLOCK_COUNT 50
#define BLOCK_SIZE  100

static uint8_t pool1[BLOCK_COUNT][BLOCK_SIZE];
p_pool_t pool_param1 = {
    .pool = pool1,
    .count = BLOCK_COUNT,
    .size = BLOCK_SIZE
};

static uint8_t pool2[BLOCK_COUNT][BLOCK_SIZE + BLOCK_COUNT];
p_pool_t pool_param2 = {
    .pool = pool2,
    .count = BLOCK_SIZE,
    .size = BLOCK_SIZE + BLOCK_COUNT
};

int test_pool() {
    mem_create(&m_pool_desc, &pool_param1);
    mem_create(&m_pool_desc, &pool_param2);

    void *ptr1 = mem_alloc(10);
    void *ptr2 = mem_alloc(20);
    void *ptr3 = mem_alloc(30);
    void *ptr4 = mem_alloc(100);
    void *ptr5 = mem_alloc(140);

    mem_free(ptr1);
    mem_free(ptr2);
    mem_free(ptr3);
    mem_free(ptr4);
    mem_free(ptr5);

    return 0;
}
