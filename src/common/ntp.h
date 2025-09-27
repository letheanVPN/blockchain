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
#include <cstdint>
#include <string>

namespace tools
{

  // requests current time via NTP from 'host_hame' using 'timeout_sec'
  // may return zero -- means error
  int64_t get_ntp_time(const std::string& host_name, size_t timeout_sec = 5);

  // request time via predefined NTP servers
  // may return zero -- mean error
  int64_t get_ntp_time();

} // namespace tools
