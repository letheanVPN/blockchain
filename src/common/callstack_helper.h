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
#include <epee/include/misc_os_dependent.h>

namespace tools
{
#if defined(WIN32)
  extern std::string get_callstack_win_x64() noexcept;
#endif

  inline std::string get_callstack() noexcept
  {
#if defined(__GNUC__)
    return epee::misc_utils::print_trace_default();
#elif defined(WIN32)
    return get_callstack_win_x64();
#else
    return "";
#endif
  }

} // namespace tools
