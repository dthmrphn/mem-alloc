cmake_minimum_required(VERSION 3.10)

project(mem
    VERSION 0.1.0
    DESCRIPTION "C memory allocators library"
    LANGUAGES C
)

# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=* -Wno-readability-identifier-length")
# set(CMAKE_C_CLANG_TIDY "clang-tidy;-checks=* -Wno-readability-identifier-length")

include(cmake/${CMAKE_SYSTEM_NAME}.cmake)

add_subdirectory(src)

# build test when bulding this project alone 
# or when this library included in some project with tests enabled  
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR BUILD_TESTING)
    include(CTest)
    add_subdirectory(test)
endif()
