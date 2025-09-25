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

#pragma once

#include <cstddef>
#include <cstring>
#include <functional>

#define POD_MAKE_COMPARABLE(space, type) \
namespace space { \
  inline bool operator==(const type &_v1, const type &_v2) { \
    return std::memcmp(&_v1, &_v2, sizeof(type)) == 0; \
  } \
  inline bool operator!=(const type &_v1, const type &_v2) { \
    return std::memcmp(&_v1, &_v2, sizeof(type)) != 0; \
  } \
}

#define POD_MAKE_LESS_OPERATOR(space, type) \
namespace space { \
  inline bool operator<(const type &_v1, const type &_v2) { \
    return std::memcmp(&_v1, &_v2, sizeof(type)) < 0; \
  } \
}

#define POD_MAKE_HASHABLE(space, type) \
 POD_MAKE_COMPARABLE(space, type) \
namespace space { \
  static_assert(sizeof(std::size_t) <= sizeof(type), "Size of " #type " must be at least that of size_t"); \
  inline std::size_t hash_value(const type &_v) { \
    return reinterpret_cast<const std::size_t &>(_v); \
  } \
} \
namespace std { \
  template<> \
  struct hash<space::type> { \
    std::size_t operator()(const space::type &_v) const { \
      return reinterpret_cast<const std::size_t &>(_v); \
    } \
  }; \
}

//
// CONSTEXPR
//
#if ( defined(_MSC_VER) && (_MSC_VER < 1800) )
  #error MS compilers prior to v 18.00 (MSVC 2013) are not supported
#endif

// compilation workaround for MSVC 2013 Update 5 wich does not support constexpr
#if ( defined(_MSC_VER) && (1800 <= _MSC_VER) && (_MSC_VER < 1900) )
  #define CONSTEXPR
#else // all other platforms or MSVC 2015 and later
  #define CONSTEXPR constexpr
#endif

