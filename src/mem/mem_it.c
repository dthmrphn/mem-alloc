#include "mem_it.h"
#include "mem.h"

static const mem_desc_t *m_desc_;

int mem_init(const void *desc, const void *params) {
    if (!desc && !params) {
        return 1;
    }
    m_desc_ = desc;
    return m_desc_->vtable.init(params);
}

void *mem_alloc(size_t size) {
    if (!m_desc_) return NULL;
    return m_desc_->vtable.allocate(size);
}

void mem_free(void *ptr) {
    if (!m_desc_) return;
    return m_desc_->vtable.deallocate(ptr);
}
