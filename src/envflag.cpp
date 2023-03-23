#include "envflag/envflag.hpp"
#include <cstdlib>

using namespace std;

namespace envflag {

namespace {

optional<string> raw_getenv(const string& name) noexcept {
    auto res = std::getenv(name.c_str());
    if (res == nullptr) {
        return nullopt;
    } else {
        return string(res);
    }
}

} // namespace

StrFlag::StrFlag(char const * name) noexcept
:   name_(name)
{}

optional<string> StrFlag::operator()() const noexcept {
    return raw_getenv(name_);
}

} // namespace envflag

