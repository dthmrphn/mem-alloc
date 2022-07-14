add_compile_options(
    "-Wextra" "-Wall"
    $<$<CONFIG:DEBUG>:-g>
    $<$<CONFIG:RELEASE>:-O0>    # there are some problems with optimization on ARM baremetal flatroms
    $<$<CONFIG:RELEASE>:-Werror>
)

add_link_options(
    $<$<CONFIG:RELEASE>:-Wl,--strip-all>
)
