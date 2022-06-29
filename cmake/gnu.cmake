message(STATUS "Bulding for Linux with GNU compiler")

add_compile_options(
    "-Wextra" "-Wall"
    $<$<CONFIG:DEBUG>:-g>
    $<$<CONFIG:RELEASE>:-O3>
    $<$<CONFIG:RELEASE>:-Werror>
)

add_link_options(
    $<$<CONFIG:RELEASE>:-Wl,--strip-all>
)
