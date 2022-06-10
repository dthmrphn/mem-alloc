#include "include/mem.h"

#include <stdio.h>

#define BLOCK_COUNT 50
#define BLOCK_SIZE  100

static uint8_t pool[BLOCK_COUNT][BLOCK_SIZE];
pparam_t pool_param = {
    .count = BLOCK_COUNT,
    .size = BLOCK_SIZE
};

int main() {
    mmalloc_init(pool, &pool_param);

    void* ptr1 = mmalloc(10);
    void* ptr2 = mmalloc(20);
    void* ptr3 = mmalloc(30);

    mfree(ptr1);
    mfree(ptr2);
    mfree(ptr3);

    return 0;
}
