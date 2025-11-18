cmake_minimum_required(VERSION 3.22)
project(ENVFLAG VERSION 1.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_compile_options(-fwrapv -Wall -DENABLE_STD_FORMAT)
# add_link_options(-fuse-ld=mold)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    # suppresses maybe-uninitialized warnings because of a gcc bug
    # https://gcc.gnu.org/bugzilla/show_bug.cgi?id=114592
    add_compile_options(-Wno-maybe-uninitialized)

    # provides more detailed diagnostic infomation for concepts.
    # works only under g++.
    add_compile_options(
        $<$<COMPILE_LANGUAGE:CXX>:-fconcepts-diagnostics-depth=10>)
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message(STATUS "release mode")
    add_compile_options(-Werror)
else()
    message(STATUS "debug mode")
    add_compile_options(-g -O0 -fsanitize=address -fvar-tracking-assignments)
    add_link_options(-fsanitize=address)
endif()

add_subdirectory(testa/cpp/)
add_subdirectory(fancy_assert/src/)

add_subdirectory(src/)
add_subdirectory(test/)
