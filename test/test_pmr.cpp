/**
 * polymorphic allocator example
 **/

#include <memory_resource>
#include <iostream>
#include <vector>
#include <chrono>

#include <cstring>

extern "C" {
#include "mem.h"
}

template<typename T>
class custom_allocator : public std::pmr::memory_resource {
public:
    custom_allocator(T* resource, std::size_t size) noexcept
        : resource_(resource), size_(size) {
            p_pool_t params = {resource_, size_, 1};
            mem_create(&m_list_desc, &params);
        }

private:
    T* resource_ = nullptr;
    T* last_ = nullptr;
    std::size_t size_ = 0;
    std::size_t chunks_ = 0;
    std::size_t allocated_ = 0;

protected:
    void* do_allocate(size_t bytes, size_t alignment) noexcept override {
        (void)alignment;
        auto p = mem_realloc(last_, bytes);
        std::cout << "\033[1;34malloc\033[0m:\taddres: " << (void*)p << "\tsize: " << bytes << "b\taligment: " << alignment << "b\n";
        last_ = static_cast<T*>(p);
        return p;
    }

    void do_deallocate(void* p, size_t bytes, size_t alignment) noexcept override {
        (void)alignment;
        (void)bytes;
        std::cout << "\033[1;31mdlloc\033[0m:\taddres: " << (void*)p << "\tsize: " << bytes << "b\taligment: " << alignment << "b\n";
        mem_free(p);
    }
 
    bool do_is_equal(const memory_resource& other) const noexcept override {
        (void)other;
        return false;
    }
};

template <typename T>
using custom_vec = std::pmr::vector<T>;
using bytearray = custom_vec<unsigned char>;

using type = unsigned int;

constexpr size_t test_size = 100;

int main() {
    type buf[test_size * 2]{};
    custom_allocator<type> allocator(buf, test_size);
    bytearray v_alloc(0, &allocator);
    std::vector<type> v_default;

    auto begin = std::chrono::steady_clock::now();
    for(size_t i = 0; i < test_size; ++i) {
        v_default.emplace_back(i);
    }
    auto end = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << "v_def: " << elapsed << " us\n";

    begin = std::chrono::steady_clock::now();
    for(size_t i = 0; i < test_size; ++i) {
        v_alloc.emplace_back(i);
    }
    end = std::chrono::steady_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << "v_alc: " << elapsed << " us\n";

    // if(std::memcmp(v_default.data(), v_alloc.data(), v_default.size())) {
    //     std::cout << "v_alc != v_def\n";
    //     return 1;
    // }

    return 0;
}
