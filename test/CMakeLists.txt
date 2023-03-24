find_package(jsoncpp QUIET)
if(jsoncpp_FOUND)
    add_compile_options(-DENVFLAG_ENABLE_JSONCPP)
endif()

add_library(all_test_flags STATIC
    all_test_flags.cpp
)
target_link_libraries(all_test_flags envflag)

add_executable(str_flag str_flag.cpp)
target_link_libraries(str_flag
    all_test_flags envflag
)
add_executable(str_flag_with_default str_flag_with_default.cpp)
target_link_libraries(str_flag_with_default
    all_test_flags envflag
)

add_executable(i64_flag i64_flag.cpp)
target_link_libraries(i64_flag
    all_test_flags envflag
)
add_executable(i64_flag_with_default i64_flag_with_default.cpp)
target_link_libraries(i64_flag_with_default
    all_test_flags envflag
)

add_executable(bool_flag bool_flag.cpp)
target_link_libraries(bool_flag
    all_test_flags envflag
)
add_executable(bool_flag_with_default bool_flag_with_default.cpp)
target_link_libraries(bool_flag_with_default
    all_test_flags envflag
)

add_executable(f64_flag f64_flag.cpp)
target_link_libraries(f64_flag
    all_test_flags envflag
)
add_executable(f64_flag_with_default f64_flag_with_default.cpp)
target_link_libraries(f64_flag_with_default
    all_test_flags envflag
)

if(jsoncpp_FOUND)
    add_executable(json_flag json_flag.cpp)
    target_link_libraries(json_flag
        all_test_flags envflag
    )
    add_executable(json_flag_with_default json_flag_with_default.cpp)
    target_link_libraries(json_flag_with_default
        all_test_flags envflag
    )
endif()

