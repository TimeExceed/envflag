find_package(jsoncpp QUIET)
if(jsoncpp_FOUND)
    message(STATUS "found jsoncpp: ${jsoncpp_VERSION}")
    add_compile_options(-DENVFLAG_ENABLE_JSONCPP)
    set(json_lib JsonCpp::JsonCpp)
else()
    set(json_lib)
endif()

add_library(envflag STATIC
    envflag.cpp
)

target_link_libraries(envflag
PUBLIC
    ${json_lib}
    fassert
)

target_include_directories(envflag
PUBLIC
    ../include/
)
