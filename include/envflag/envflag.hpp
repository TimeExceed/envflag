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

#include "fassert.hpp"
#include <typeinfo>
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
    const char* name_;
};

template<typename T, typename ConcreteClass>
class FlagWithParser {
public:
    typedef T ReturnType;

    FlagWithParser(const FlagWithParser&) =delete;
    FlagWithParser& operator=(const FlagWithParser&) =delete;
    FlagWithParser(FlagWithParser&&) =delete;
    FlagWithParser& operator=(FlagWithParser&&) =delete;

    explicit FlagWithParser(
        ::std::function<T(const char*, const ::std::string_view&)> parser,
        const char* name) noexcept
    :   defined_type_(typeid(ConcreteClass).name()),
        parser_(std::move(parser)),
        raw_flag_(name)
    {}

    ::std::optional<T> operator()() const noexcept {
        auto import_type = typeid(ConcreteClass).name();
        FASSERT(import_type == defined_type_)
            .hint("raw flag: {}", raw_flag_.name_)
            .hint("import type: {}", import_type)
            .hint("defined type: {}", defined_type_)
            .what("A flag has different types between its definition and importation.");
        auto res = raw_flag_();
        if (res) {
            return std::move(parser_(raw_flag_.name_, *res));
        } else {
            return std::nullopt;
        }
    }

private:
    char const * defined_type_;
    ::std::function<T(const char*, const ::std::string_view&)> parser_;
    RawFlag raw_flag_;
};

template<typename T, typename ConcreteClass>
class FlagWithDefault {
public:
    typedef T ReturnType;

    explicit FlagWithDefault(
        ::std::function<T(const char*, const ::std::string_view&)> parser,
        const char* name,
        T default_value) noexcept
    :   flag_(parser, name),
        default_value_(std::move(default_value))
    {}

    T operator()() const noexcept {
        auto res = flag_();
        if (res) {
            return std::move(*res);
        } else {
            return default_value_;
        }
    }

private:
    FlagWithParser<T, ConcreteClass> flag_;
    ReturnType default_value_;
};

} // namespace envflag

#define IN_ENVFLAG_HPP
#include "envflag.ipp"

#define DEFINE_STR_FLAG(flag, _usage) \
    ::envflag::StrFlag flag(#flag);
#define IMPORT_STR_FLAG(flag) \
    extern ::envflag::StrFlag flag;
#define DEFINE_STR_FLAG_WITH_DEFAULT(flag, _usage, default_value) \
    ::envflag::DefaultedStrFlag flag(#flag, default_value);
#define IMPORT_STR_FLAG_WITH_DEFAULT(flag) \
    extern ::envflag::DefaultedStrFlag flag;

#define DEFINE_I64_FLAG(flag, _usage) \
    ::envflag::I64Flag flag(#flag);
#define IMPORT_I64_FLAG(flag) \
    extern ::envflag::I64Flag flag;
#define DEFINE_I64_FLAG_WITH_DEFAULT(flag, _usage, default_value) \
    ::envflag::DefaultedI64Flag flag(#flag, default_value);
#define IMPORT_I64_FLAG_WITH_DEFAULT(flag) \
    extern ::envflag::DefaultedI64Flag flag;

#define DEFINE_F64_FLAG(flag, _usage) \
    ::envflag::F64Flag flag(#flag);
#define IMPORT_F64_FLAG(flag) \
    extern ::envflag::F64Flag flag;
#define DEFINE_F64_FLAG_WITH_DEFAULT(flag, _usage, default_value) \
    ::envflag::DefaultedF64Flag flag(#flag, default_value);
#define IMPORT_F64_FLAG_WITH_DEFAULT(flag) \
    extern ::envflag::DefaultedF64Flag flag;

#define DEFINE_BOOL_FLAG(flag, _usage) \
    ::envflag::BoolFlag flag(#flag);
#define IMPORT_BOOL_FLAG(flag) \
    extern ::envflag::BoolFlag flag;
#define DEFINE_BOOL_FLAG_WITH_DEFAULT(flag, _usage, default_value) \
    ::envflag::DefaultedBoolFlag flag(#flag, default_value);
#define IMPORT_BOOL_FLAG_WITH_DEFAULT(flag) \
    extern ::envflag::DefaultedBoolFlag flag;

#ifdef ENVFLAG_ENABLE_JSONCPP
#define DEFINE_JSON_FLAG(flag, _usage) \
    ::envflag::JsonFlag flag(#flag);
#define IMPORT_JSON_FLAG(flag) \
    extern ::envflag::JsonFlag flag;
#define DEFINE_JSON_FLAG_WITH_DEFAULT(flag, _usage, default_value) \
    ::envflag::DefaultedJsonFlag flag(#flag, default_value);
#define IMPORT_JSON_FLAG_WITH_DEFAULT(flag) \
    extern ::envflag::DefaultedJsonFlag flag;
#endif

#undef IN_ENVFLAG_HPP
#endif /* ENVFLAG_HPP */
