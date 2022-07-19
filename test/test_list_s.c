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

int main() {
    int rv = 0;

    if (mem_create(&m_list_desc, &pool_param)) {
        return 1;
    }
    const size_t test_sizes[] = {1000, 2000, 3000, 3500};

    void *ptr = NULL;
    for (size_t i = 0; i < (sizeof(test_sizes) / sizeof(test_sizes[0])); ++i) {
        ptr = mem_realloc(ptr, test_sizes[i]);
        if (!ptr) {
            rv = 1;
            break;
        }
    }
    mem_free(ptr);

    ptr = mem_realloc(ptr, sizeof(pool));
    if (ptr) {
        rv = 1;
    }

    mem_free(ptr);

    return rv;
}
