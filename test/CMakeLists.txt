add_executable(test_list test_list.c)
add_executable(test_list_s test_list_s.c)
add_executable(test_pool test_pool.c)

target_link_libraries(test_list PRIVATE mem)
target_link_libraries(test_list_s PRIVATE mem)
target_link_libraries(test_pool PRIVATE mem)

add_test(NAME test_list COMMAND test_list)
add_test(NAME test_list_s COMMAND test_list_s)
add_test(NAME test_pool COMMAND test_pool)
