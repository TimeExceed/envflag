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


class StrFlag: public FlagWithDefaultAndParser<::std::string_view> {
public:
    typedef FlagWithDefaultAndParser<::std::string_view> ParentType;
    explicit StrFlag(char const * name) noexcept;
    explicit StrFlag(char const * name, char const* default_value) noexcept;
};

class I64Flag: public FlagWithDefaultAndParser<int64_t> {
public:
    typedef FlagWithDefaultAndParser<int64_t> ParentType;
    explicit I64Flag(char const * name) noexcept;
    explicit I64Flag(char const * name, int64_t default_value) noexcept;
};

class F64Flag: public FlagWithDefaultAndParser<double> {
public:
    typedef FlagWithDefaultAndParser<double> ParentType;
    explicit F64Flag(char const * name) noexcept;
    explicit F64Flag(char const * name, double default_value) noexcept;
};

class BoolFlag: public FlagWithDefaultAndParser<bool> {
public:
    typedef FlagWithDefaultAndParser<bool> ParentType;
    explicit BoolFlag(char const * name) noexcept;
    explicit BoolFlag(char const * name, bool default_value) noexcept;
};

#ifdef ENVFLAG_ENABLE_JSONCPP
class JsonFlag: public FlagWithDefaultAndParser<::Json::Value> {
public:
    typedef FlagWithDefaultAndParser<::Json::Value> ParentType;
    explicit JsonFlag(char const * name) noexcept;
    explicit JsonFlag(char const * name, char const* default_value) noexcept;
};
#endif

} // namespace envflag
