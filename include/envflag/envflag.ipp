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
#ifndef IN_ENVFLAG_HPP
#error "envflag.ipp" must not be included. Include "envflag.hpp" instead.
#endif

#include <cinttypes>

#ifdef ENVFLAG_ENABLE_JSONCPP
#include <json/value.h>
#endif

namespace envflag {


class StrFlag: public FlagWithParser<::std::string_view, StrFlag> {
public:
    typedef FlagWithParser<::std::string_view, StrFlag> ParentType;
    explicit StrFlag(char const * name) noexcept;
};

class DefaultedStrFlag: public FlagWithDefault<::std::string_view, DefaultedStrFlag> {
public:
    typedef FlagWithDefault<::std::string_view, DefaultedStrFlag> ParentType;
    explicit DefaultedStrFlag(char const * name, char const* default_value) noexcept;
};

class I64Flag: public FlagWithParser<int64_t, I64Flag> {
public:
    typedef FlagWithParser<int64_t, I64Flag> ParentType;
    explicit I64Flag(char const * name) noexcept;
};

class DefaultedI64Flag: public FlagWithDefault<int64_t, DefaultedI64Flag> {
public:
    typedef FlagWithDefault<int64_t, DefaultedI64Flag> ParentType;
    explicit DefaultedI64Flag(char const * name, int64_t default_value) noexcept;
};

class F64Flag: public FlagWithParser<double, F64Flag> {
public:
    typedef FlagWithParser<double, F64Flag> ParentType;
    explicit F64Flag(char const * name) noexcept;
};

class DefaultedF64Flag: public FlagWithDefault<double, DefaultedF64Flag> {
public:
    typedef FlagWithDefault<double, DefaultedF64Flag> ParentType;
    explicit DefaultedF64Flag(char const * name, double default_value) noexcept;
};

class BoolFlag: public FlagWithParser<bool, BoolFlag> {
public:
    typedef FlagWithParser<bool, BoolFlag> ParentType;
    explicit BoolFlag(char const * name) noexcept;
};

class DefaultedBoolFlag: public FlagWithDefault<bool, DefaultedBoolFlag> {
public:
    typedef FlagWithDefault<bool, DefaultedBoolFlag> ParentType;
    explicit DefaultedBoolFlag(char const * name, bool default_value) noexcept;
};

#ifdef ENVFLAG_ENABLE_JSONCPP
class JsonFlag: public FlagWithParser<::Json::Value, JsonFlag> {
public:
    typedef FlagWithParser<::Json::Value, JsonFlag> ParentType;
    explicit JsonFlag(char const * name) noexcept;
};

class DefaultedJsonFlag: public FlagWithDefault<::Json::Value, JsonFlag> {
public:
    typedef FlagWithDefault<::Json::Value, JsonFlag> ParentType;
    explicit DefaultedJsonFlag(char const * name, char const* default_value) noexcept;
};

#endif

} // namespace envflag
