#pragma once
// BSD 3-Clause License

// Copyright (c) 2023, Taoda (https://github.com/TimeExceed/envflag)

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.

// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#ifndef ENVFLAG_HPP
#define ENVFLAG_HPP

#include <functional>
#include <string_view>
#include <optional>

namespace envflag {

class RawFlag {
public:
    RawFlag(const RawFlag&) =delete;
    RawFlag& operator=(const RawFlag&) =delete;
    RawFlag(RawFlag&&) =delete;
    RawFlag& operator=(RawFlag&&) =delete;

    explicit RawFlag(char const * name) noexcept;

    ::std::optional<::std::string_view> operator()() const noexcept;
    ::std::string_view name_;
};

template<typename T>
class FlagWithDefaultAndParser {
public:
    typedef T ReturnType;

    FlagWithDefaultAndParser(const FlagWithDefaultAndParser&) =delete;
    FlagWithDefaultAndParser& operator=(const FlagWithDefaultAndParser&) =delete;
    FlagWithDefaultAndParser(FlagWithDefaultAndParser&&) =delete;
    FlagWithDefaultAndParser& operator=(FlagWithDefaultAndParser&&) =delete;

    explicit FlagWithDefaultAndParser(
        ::std::function<T(const ::std::string_view&, const ::std::string_view&)> parser,
        const char* name) noexcept
    :   parser_(std::move(parser)),
        raw_flag_(name)
    {}

    explicit FlagWithDefaultAndParser(
        ::std::function<T(const ::std::string_view&, const ::std::string_view&)> parser,
        const char* name,
        T default_value) noexcept
    :   parser_(std::move(parser)),
        raw_flag_(name),
        default_value_(std::move(default_value))
    {}

    ::std::optional<T> operator()() const noexcept {
        auto res = raw_flag_();
        if (res) {
            return std::move(parser_(raw_flag_.name_, *res));
        } else {
            return default_value_;
        }
    }

private:
    ::std::function<T(const ::std::string_view&, const ::std::string_view&)> parser_;
    RawFlag raw_flag_;
    ::std::optional<T> default_value_;
};

} // namespace envflag

#define IN_ENVFLAG_HPP
#include "envflag.ipp"

#define DEFINE_STR_FLAG(flag, _usage) \
    ::envflag::StrFlag flag(#flag);
#define DEFINE_STR_FLAG_WITH_DEFAULT(flag, _usage, default_value) \
    ::envflag::StrFlag flag(#flag, default_value);
#define IMPORT_STR_FLAG(flag) \
    extern ::envflag::StrFlag flag;

#define DEFINE_I64_FLAG(flag, _usage) \
    ::envflag::I64Flag flag(#flag);
#define DEFINE_I64_FLAG_WITH_DEFAULT(flag, _usage, default_value) \
    ::envflag::I64Flag flag(#flag, default_value);
#define IMPORT_I64_FLAG(flag) \
    extern ::envflag::I64Flag flag;

#define DEFINE_F64_FLAG(flag, _usage) \
    ::envflag::F64Flag flag(#flag);
#define DEFINE_F64_FLAG_WITH_DEFAULT(flag, _usage, default_value) \
    ::envflag::F64Flag flag(#flag, default_value);
#define IMPORT_F64_FLAG(flag) \
    extern ::envflag::F64Flag flag;

#define DEFINE_BOOL_FLAG(flag, _usage) \
    ::envflag::BoolFlag flag(#flag);
#define DEFINE_BOOL_FLAG_WITH_DEFAULT(flag, _usage, default_value) \
    ::envflag::BoolFlag flag(#flag, default_value);
#define IMPORT_BOOL_FLAG(flag) \
    extern ::envflag::BoolFlag flag;

#undef IN_ENVFLAG_HPP
#endif /* ENVFLAG_HPP */
