cmake_minimum_required(VERSION 3.22)
project(ENVFLAG VERSION 1.1)

add_compile_options(
    $<$<COMPILE_LANGUAGE:CXX>:--std=c++20> $<$<COMPILE_LANGUAGE:C>:--std=c17>
    -fwrapv -Wall -DENABLE_STD_FORMAT)

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
