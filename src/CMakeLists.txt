add_library(envflag STATIC
    envflag.cpp
)

target_link_libraries(envflag
PUBLIC
    fassert
)

target_include_directories(envflag
PUBLIC
    ../include/
)
