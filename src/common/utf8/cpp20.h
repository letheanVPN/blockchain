// Copyright (c) 2014-2018 Zano Project
// Copyright (c) 2014-2018 The Louisdor Project
// Copyright (c) 2012-2013 The Boolberry developers
// Copyright (c) 2017-2025 Lethean (https://lt.hn)
//
// Licensed under the European Union Public Licence (EUPL) version 1.2.
// You may obtain a copy of the licence at:
//
//     https://joinup.ec.europa.eu/software/page/eupl/licence-eupl
//
// The EUPL is a copyleft licence that is compatible with the MIT/X11
// licence used by the original projects; the MIT terms are therefore
// considered “grandfathered” under the EUPL for this code.
//
// SPDX‑License‑Identifier: EUPL-1.2
//

#ifndef UTF8_FOR_CPP_207e906c01_03a3_4daf_b420_ea7ea952b3c9
#define UTF8_FOR_CPP_207e906c01_03a3_4daf_b420_ea7ea952b3c9

#include "cpp17.h"

namespace utf8
{
    inline std::u8string utf16tou8(const std::u16string& s)
    {
        std::u8string result;
        utf16to8(s.begin(), s.end(), std::back_inserter(result));
        return result;
    }

    inline std::u8string utf16tou8(std::u16string_view s)
    {
        std::u8string result;
        utf16to8(s.begin(), s.end(), std::back_inserter(result));
        return result;
    }

    inline std::u16string utf8to16(const std::u8string& s)
    {
        std::u16string result;
        utf8to16(s.begin(), s.end(), std::back_inserter(result));
        return result;
    }

    inline std::u16string utf8to16(const std::u8string_view& s)
    {
        std::u16string result;
        utf8to16(s.begin(), s.end(), std::back_inserter(result));
        return result;
    }

    inline std::u8string utf32tou8(const std::u32string& s)
    {
        std::u8string result;
        utf32to8(s.begin(), s.end(), std::back_inserter(result));
        return result;
    }

    inline std::u8string utf32tou8(const std::u32string_view& s)
    {
        std::u8string result;
        utf32to8(s.begin(), s.end(), std::back_inserter(result));
        return result;
    }

    inline std::u32string utf8to32(const std::u8string& s)
    {
        std::u32string result;
        utf8to32(s.begin(), s.end(), std::back_inserter(result));
        return result;
    }

    inline std::u32string utf8to32(const std::u8string_view& s)
    {
        std::u32string result;
        utf8to32(s.begin(), s.end(), std::back_inserter(result));
        return result;
    }

    inline std::size_t find_invalid(const std::u8string& s)
    {
        std::u8string::const_iterator invalid = find_invalid(s.begin(), s.end());
        return (invalid == s.end()) ? std::string_view::npos : static_cast<std::size_t>(invalid - s.begin());
    }

    inline bool is_valid(const std::u8string& s)
    {
        return is_valid(s.begin(), s.end());
    }

    inline std::u8string replace_invalid(const std::u8string& s, char32_t replacement)
    {
        std::u8string result;
        replace_invalid(s.begin(), s.end(), std::back_inserter(result), replacement);
        return result;
    }

    inline std::u8string replace_invalid(const std::u8string& s)
    {
        std::u8string result;
        replace_invalid(s.begin(), s.end(), std::back_inserter(result));
        return result;
    }

    inline bool starts_with_bom(const std::u8string& s)
    {
        return starts_with_bom(s.begin(), s.end());
    }
 
} // namespace utf8

#endif // header guard

