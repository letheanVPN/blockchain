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

#include "currency_format_utils.h"
#include "etc_custom_serialization.h"

namespace bc_services
{
  std::string transform_amount_to_string(const uint64_t& a)
  {
//     double d = static_cast<double>(a);
//     d /= ETC_AMOUNT_DIVIDER;
    return std::to_string(a);//print_money(a, ETC_AMOUNT_DIVIDER_DECIMAL_POINT);
  }

  uint64_t transform_string_to_amount(const std::string& d)
  {
    uint64_t n = 0;
    epee::string_tools::get_xtype_from_string(n, d);
    return n;
  }
}