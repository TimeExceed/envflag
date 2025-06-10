#include "envflag/envflag.hpp"

#ifdef ENVFLAG_ENABLE_JSONCPP
#include <json/reader.h>
#endif

#include "fassert.hpp"
#include <memory>
#include <charconv>
#include <cstdlib>
#include <cctype>

using namespace std;

namespace envflag {

RawFlag::RawFlag(char const * name) noexcept
:   name_(name)
{}

optional<string_view> RawFlag::operator()() const noexcept {
    auto res = std::getenv(name_);
    if (res == nullptr) {
        return nullopt;
    } else {
        return string_view(res);
    }
}

namespace {

string_view sv_identiy(const string_view&, const string_view& in) noexcept {
    return in;
}

} // namespace

StrFlag::StrFlag(char const * name) noexcept
:   ParentType(sv_identiy, name)
{}

DefaultedStrFlag::DefaultedStrFlag(
    char const * name,
    char const * default_value) noexcept
:   ParentType(sv_identiy, name, default_value)
{}

namespace {

int64_t parse_i64(const char* name, const string_view& str) noexcept {
    int64_t result = 0;
    auto [ptr, ec] { from_chars(str.data(), str.data() + str.size(), result) };
    if (ec == std::errc::invalid_argument) {
        FASSERT(false)
            ("env={}", name)
            ("value={}", str)
            .what("That isn't a number.");
    } else if (ec == std::errc::result_out_of_range) {
        FASSERT(false)
            ("env={}", name)
            ("value={}", str)
            .what("This number is larger than an int64_t.");
    } else if (ptr != str.data() + str.size()) {
        FASSERT(false)
            ("env={}", name)
            ("value={}", str)
            .what("Not everything can be parsed.");
    }
    return result;
}

} // namespace

I64Flag::I64Flag(char const * name) noexcept
:   ParentType(parse_i64, name)
{}

DefaultedI64Flag::DefaultedI64Flag(
    char const * name,
    int64_t default_value) noexcept
:   ParentType(parse_i64, name, default_value)
{}

namespace {

bool parse_bool(const char* name, const string_view& value) noexcept {
    const char TRUE[] = "true";
    const size_t TRUE_LEN = sizeof(TRUE) / sizeof(TRUE[0]) - 1;
    const char FALSE[] = "false";
    const size_t FALSE_LEN = sizeof(FALSE) / sizeof(FALSE[0]) - 1;
    string_view true_view(TRUE, TRUE_LEN);
    string_view false_view(FALSE, FALSE_LEN);
    if (value == true_view) {
        return true;
    } else if (value == false_view) {
        return false;
    } else {
        FASSERT(false)
            ("env={}", name)
            ("value={}", value)
            .what("Unrecognized bool value.");
        return false;
    }
}

} // namespace

BoolFlag::BoolFlag(char const * name) noexcept
:   ParentType(parse_bool, name)
{}

DefaultedBoolFlag::DefaultedBoolFlag(
    char const * name,
    bool default_value) noexcept
:   ParentType(parse_bool, name, default_value)
{}

namespace {
double parse_f64(const char* name, const string_view& value) noexcept {
    double res = 0;
    const char* s = value.data();
    const char* e = s + value.size();
    for(; s < e && isdigit(*s); ++s) {
        res *= 10;
        res += *s - '0';
    }
    if (s == e) {
        return res;
    }
    FASSERT(*s == '.')
        ("current={}", *s)
        ("value={}", value);
    double base = 0.1;
    for(++s; s < e && isdigit(*s); ++s) {
        double d = *s - '0';
        res += base * d;
        base *= 0.1;
    }
    FASSERT(s == e)
        ("current={}", *s)
        ("value={}", value);
    return res;
}
} // namespace

F64Flag::F64Flag(char const * name) noexcept
:   ParentType(parse_f64, name)
{}

DefaultedF64Flag::DefaultedF64Flag(
    char const * name,
    double default_value) noexcept
:   ParentType(parse_f64, name, default_value)
{}

#ifdef ENVFLAG_ENABLE_JSONCPP

namespace {

::Json::Value parse_json(const char* name, const string_view& value) noexcept {
    ::Json::Value res;
    ::Json::CharReaderBuilder builder;
    builder["collectComments"] = false;
    unique_ptr<::Json::CharReader> reader(builder.newCharReader());
    ::Json::String errs;
    bool ok = reader->parse(value.data(), value.data() + value.size(), &res, &errs);
    FASSERT(ok)
        ("env={}", name)
        ("value={}", value)
        ("error={}", errs)
        .what("Invalid JSON text");
    return res;
}

} // namespace

JsonFlag::JsonFlag(char const * name) noexcept
:   ParentType(parse_json, name)
{}

DefaultedJsonFlag::DefaultedJsonFlag(char const * name, char const* default_value) noexcept
:   ParentType(parse_json, name, parse_json(name, default_value))
{}
#endif

} // namespace envflag

