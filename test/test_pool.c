#include "mem.h"

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

int main() {
    mem_create(&m_pool_desc, &pool_param1);
    mem_create(&m_pool_desc, &pool_param2);

    void *ptr = NULL;
    size_t test_sizes[] = {10, 20, 30, 40, 50, 100, 140};

    int rv = 0;

    for (size_t i = 0; i < (sizeof(test_sizes) / sizeof(test_sizes[0])); ++i) {
        ptr = mem_alloc(test_sizes[i]);
        if (!ptr) {
            rv = 1;
            break;
        }

        mem_free(ptr);
    }

    return rv;
}
