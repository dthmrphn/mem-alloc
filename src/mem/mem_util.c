#include "mem_it.h"

void mem_copy(void *a, const void *b, size_t size) {
    while (size--) {
        *(int*)a++ = *(int*)b++;
    }
}