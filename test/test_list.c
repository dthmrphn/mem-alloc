#include "mem.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static uint8_t pool[10000];
p_pool_t pool_param = {
    .pool = pool,
    .size = sizeof(pool),
    .count = 1
};

void set_buf(void *buf, size_t size) {
    uint8_t *ptr = buf;
    size_t i = 0;
    while (i < size) {
        ptr[i++] = (uint8_t)rand(); 
    }
}

int main() {
    int rv = 1;
    uint8_t *ptr = NULL;

    do {
        if (mem_create(&m_list_desc, &pool_param)) {
            break;
        }

        uint8_t buf[100];

        ptr = mem_alloc(sizeof(buf));
        if (!ptr) {
            break;
        }

        set_buf(ptr, sizeof(buf));
        memcpy(buf, ptr, sizeof(buf));

        ptr = mem_realloc(ptr, sizeof(buf) * 2);
        if (!ptr) {
            break;
        }

        if (memcmp(ptr, buf, sizeof(buf))) {
            break;
        }
        rv = 0;
    } while (0);

    mem_free(ptr);

    return rv;
}
