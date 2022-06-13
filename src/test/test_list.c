#include "mem.h"
#include "tests.h"

#include <stddef.h>

static uint8_t pool[1000];
p_pool_t pool_param = {
    .pool = pool,
    .count = 1,
    .size = 1000
};

int test_list() {
    mem_create(&m_list_desc, &pool_param);

    void *ptr1 = mem_alloc(10);
    void *ptr2 = mem_alloc(100);

    mem_free(ptr2);

    void *ptr3 = mem_alloc(20);
    void *ptr4 = mem_alloc(30);
    void *ptr5 = mem_alloc(140);

    mem_free(ptr1);
    mem_free(ptr3);
    mem_free(ptr4);
    mem_free(ptr5);

    return 0;
}