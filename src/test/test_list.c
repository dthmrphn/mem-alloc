#include "mem.h"
#include "tests.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

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

    void *ptr1 = mem_alloc(100);
    void *ptr2 = mem_alloc(100);
    void *ptr3 = mem_alloc(100);
    void *ptr4 = mem_alloc(100);
    void *ptr5 = mem_alloc(100);
    void *ptr6 = mem_alloc(100);
    void *ptr7 = mem_alloc(100);
    void *ptr8 = mem_alloc(1);
    void *ptr9 = mem_alloc(1);
    void *ptr10 = mem_alloc(1);

    set_buf(ptr1, 100);
    set_buf(ptr2, 100);
    set_buf(ptr3, 100);
    set_buf(ptr4, 100);
    set_buf(ptr5, 100);
    set_buf(ptr6, 100);
    set_buf(ptr7, 100);
    set_buf(ptr8, 1);
    set_buf(ptr9, 1);
    set_buf(ptr10, 1);

    mem_free(ptr10);
    mem_free(ptr9);
    mem_free(ptr8);

    ptr8 = mem_alloc(100);
    ptr9 = mem_alloc(100);
    ptr10 = mem_alloc(100);

    mem_free(ptr7);
    mem_free(ptr6);
    mem_free(ptr5);

    mem_free(ptr10);
    mem_free(ptr9);
    mem_free(ptr8);

    mem_free(ptr4);
    mem_free(ptr3);
    mem_free(ptr2);
    mem_free(ptr1);



    return 0;
}