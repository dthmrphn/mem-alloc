message(STATUS "Bulding for Linux with GNU compiler")

add_compile_options(
    "-Wextra" "-Wall"

    $<$<CONFIG:DEBUG>:-g>
    $<$<CONFIG:RELEASE>:-O3>
    $<$<CONFIG:RELEASE>:-Werror>
    $<$<COMPILE_LANGUAGE:CXX>:-std=c++17>
    $<$<COMPILE_LANGUAGE:C>:-std=c11>
)

add_link_options(
    $<$<CONFIG:RELEASE>:-Wl,--strip-all>
)
