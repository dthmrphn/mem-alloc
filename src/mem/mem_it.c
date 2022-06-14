#include "mem_it.h"
#include "mem.h"

static const mem_desc_t *m_desc_;

/**
 * @brief creates memory resource
 * 
 * @param desc pointer to allocator descriptor
 * @param params pointer to allocator params
 * @return 0 if success 
 */
int mem_create(const void *desc, const void *params) {
    if (!desc && !params) {
        return 1;
    }
    m_desc_ = desc;
    return m_desc_->vtable.init(params);
}

/**
 * @brief allocates memory block
 * 
 * @param size size of data to be allocated
 * @return pointer to data block or NULL
 */
void *mem_alloc(size_t size) {
    if (!m_desc_) return NULL;
    return m_desc_->vtable.alloc(size);
}

/**
 * @brief deallocates memory block
 * 
 * @param ptr pointer to memory block to be freed
 */
void mem_free(void *ptr) {
    if (!m_desc_) return;
    return m_desc_->vtable.dealloc(ptr);
}
