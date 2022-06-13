
add_compile_options(
    $<$<CONFIG:DEBUG>:-g>
    $<$<CONFIG:RELEASE>:-O3>
)

add_link_options(
    $<$<CONFIG:RELEASE>:-Wl,--strip-all>
)

add_library(mem STATIC 
    mem/mem_it.c
    mem/mem_pool_p.c
    mem/mem_list_p.c
)

add_executable(test test/test_list.c)

target_link_libraries(test PRIVATE mem)