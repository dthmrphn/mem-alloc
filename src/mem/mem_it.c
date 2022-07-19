#include "mem_it.h"

static const mem_desc_t *m_desc_;

/**
 * @brief creates memory resource
 * 
 * @param desc pointer to allocator descriptor
 * @param params pointer to allocator params
 * @return 0 if success 
 */
int mem_create(const void *desc, const void *params) {
    if (!desc || !params) {
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
    // if (!m_desc_) return NULL;
    // return m_desc_->vtable.m_alloc(size);

    return !m_desc_ ? NULL : m_desc_->vtable.m_alloc(size);
}

/**
 * @brief deallocates memory block
 * 
 * @param ptr pointer to memory block to be freed
 */
void mem_free(void *ptr) {
    // if (!m_desc_) return;
    // return m_desc_->vtable.d_alloc(ptr);

    return !m_desc_ ? NULL : m_desc_->vtable.d_alloc(ptr);
}

/**
 * @brief reallocates previously allocated memory block
 * 
 * @param ptr pointer to memory block to be reallocated
 * @param size new size
 * @return pointer to data block or NULL
 */
void *mem_realloc(void *ptr, size_t size) {
    // if (!m_desc_) return NULL;
    // return m_desc_->vtable.r_alloc(ptr, size);

    return !m_desc_ ? NULL : m_desc_->vtable.r_alloc(ptr, size);
}
