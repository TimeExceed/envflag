#include "envflag/envflag.hpp"
#include "fassert.hpp"
#include <charconv>
#include <cstdlib>
#include <cctype>

using namespace std;

namespace envflag {

RawFlag::RawFlag(char const * name) noexcept
:   name_(name)
{}

optional<string_view> RawFlag::operator()() const noexcept {
    auto res = std::getenv(name_.data());
    if (res == nullptr) {
        return nullopt;
    } else {
        return std::move(string_view(res));
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

StrFlag::StrFlag(
    char const * name,
    char const * default_value) noexcept
:   ParentType(sv_identiy, name, default_value)
{}

namespace {

int64_t parse_i64(const string_view& name, const string_view& str) noexcept {
    int64_t result = 0;
    auto [ptr, ec] { from_chars(str.data(), str.data() + str.size(), result) };
    if (ec == std::errc::invalid_argument) {
        FASSERT(false)
            (name)
            .what("That isn't a number.");
    } else if (ec == std::errc::result_out_of_range) {
        FASSERT(false)
            (name)
            .what("This number is larger than an int64_t.");
    } else if (ptr != str.data() + str.size()) {
        FASSERT(false)
            (name)
            (str)
            .what("Not everything can be parsed.");
    }
    return result;
}

} // namespace

I64Flag::I64Flag(char const * name) noexcept
:   ParentType(parse_i64, name)
{}

I64Flag::I64Flag(
    char const * name,
    int64_t default_value) noexcept
:   ParentType(parse_i64, name, default_value)
{}

namespace {

bool parse_bool(const string_view& name, const string_view& value) noexcept {
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
            (name)
            (value)
            .what("Unrecognized bool value.");
        return false;
    }
}

} // namespace

BoolFlag::BoolFlag(char const * name) noexcept
:   ParentType(parse_bool, name)
{}

BoolFlag::BoolFlag(
    char const * name,
    bool default_value) noexcept
:   ParentType(parse_bool, name, default_value)
{}

namespace {
double parse_f64(const string_view& name, const string_view& value) noexcept {
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
        (*s)
        (value);
    double base = 0.1;
    for(++s; s < e && isdigit(*s); ++s) {
        double d = *s - '0';
        res += base * d;
    }
    FASSERT(s == e)
        (*s)
        (value);
    return res;
}
} // namespace

F64Flag::F64Flag(char const * name) noexcept
:   ParentType(parse_f64, name)
{}

F64Flag::F64Flag(
    char const * name,
    double default_value) noexcept
:   ParentType(parse_f64, name, default_value)
{}

} // namespace envflag

