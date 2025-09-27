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
#include <memory>
#include <boost/multiprecision/cpp_int.hpp>


#include "serialization.h"

template <template <bool> class Archive>
inline bool do_serialize(Archive<false>& ar, boost::multiprecision::uint128_t& diff)
{
  uint64_t hi = 0;
  uint64_t lo = 0;
  ar.serialize_uint(hi);
  ar.serialize_uint(lo);

  diff = hi;
  diff = (diff << 64) | lo;
  return true;
}


template <template <bool> class Archive>
inline bool do_serialize(Archive<true>& ar, boost::multiprecision::uint128_t& diff_)
{
  uint64_t hi = (diff_ >> 64).convert_to<uint64_t>();
  uint64_t lo = (diff_ & (0xFFFFFFFFFFFFFFFFLL)).convert_to<uint64_t>();
  ar.serialize_uint(hi);
  ar.serialize_uint(lo);
  return true;
}
