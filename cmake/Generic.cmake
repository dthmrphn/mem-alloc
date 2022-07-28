add_compile_options(
    "-Wextra" "-Wall"
    $<$<CONFIG:DEBUG>:-g>
    $<$<CONFIG:RELEASE>:-O2>   
    $<$<CONFIG:RELEASE>:-Werror>
)

add_link_options(
    $<$<CONFIG:RELEASE>:-Wl,--strip-all>
)
