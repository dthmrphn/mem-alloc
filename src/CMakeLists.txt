add_library(${PROJECT_NAME} STATIC 
    mem/mem_it.c
    mem/mem_pool_p.c
    mem/mem_list_p.c
    mem/mem_util.c
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
