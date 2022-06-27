#include "mem.h"
#include "tests.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static uint8_t pool[10000];
p_pool_t pool_param = {
    .pool = pool,
    .count = 1,
    .size = sizeof(pool)
};

void set_buf(void *buf, size_t size) {
    uint8_t *ptr = buf;
    size_t i = 0;
    while (i < size) {
        ptr[i++] = (uint8_t)rand(); 
    }
}

int test_list() {
    mem_create(&m_list_desc, &pool_param);

    uint8_t buf[100];

    void *ptr = mem_alloc(sizeof(buf));
    set_buf(ptr, sizeof(buf));
    memcpy(buf, ptr, sizeof(buf));

    ptr = mem_realloc(ptr, sizeof(buf) * 2);

    if (memcmp(ptr, buf, sizeof(buf))) {
        printf("buffer value mismatch\n");
    }

    mem_free(ptr);

    return 0;
}
