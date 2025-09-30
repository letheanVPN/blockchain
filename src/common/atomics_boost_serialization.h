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

#include <atomic>

namespace boost
{
  namespace serialization
  {
    template <class Archive, class value_t>
    inline void save(Archive &a, const std::atomic<value_t> &x, const boost::serialization::version_type ver)
    {
      a << x.load();
    }

    template <class Archive, class value_t>
    inline void load(Archive &a, std::atomic<value_t> &x, const boost::serialization::version_type ver)
    {
      value_t s = AUTO_VAL_INIT(s);
      a >> s;
      x.store(s);
    }
    template <class Archive, class value_t>
    inline void serialize(Archive &a, std::atomic<value_t> &x, const boost::serialization::version_type ver)
    {
      split_free(a, x, ver);
    }
  }
}
