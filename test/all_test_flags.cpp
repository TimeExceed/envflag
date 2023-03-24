#include "envflag/envflag.hpp"

DEFINE_STR_FLAG(str_flag,
    "a str flag for testing");
DEFINE_STR_FLAG_WITH_DEFAULT(str_flag_with_default,
    "a str flag for testing",
    "haha");

DEFINE_I64_FLAG(i64_flag,
    "a i64 flag for testing");
DEFINE_I64_FLAG_WITH_DEFAULT(i64_flag_with_default,
    "a i64 flag for testing",
    123);

DEFINE_BOOL_FLAG(bool_flag,
    "a bool flag for testing");
DEFINE_BOOL_FLAG_WITH_DEFAULT(bool_flag_with_default,
    "a bool flag for testing",
    true);

DEFINE_F64_FLAG(f64_flag,
    "a f64(double) flag for testing");
DEFINE_F64_FLAG_WITH_DEFAULT(f64_flag_with_default,
    "a f64(double) flag for testing",
    123.0);

#ifdef ENVFLAG_ENABLE_JSONCPP
DEFINE_JSON_FLAG(json_flag,
    "a json flag for testing");
DEFINE_JSON_FLAG_WITH_DEFAULT(json_flag_with_default,
    "a json flag for testing",
    "[123]");
#endif
