cmake_minimum_required(VERSION 3.10)

project(mem
    VERSION 0.1.0
    LANGUAGES C
)

include(CTest)
add_subdirectory(cmake)

add_subdirectory(src)
add_subdirectory(test)
