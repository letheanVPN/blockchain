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
#include "p2p_protocol_defs.h"
#include "common/crypto_serialization.h"

namespace boost
{
  namespace serialization
  {
    template <class Archive, class ver_type>
    inline void serialize(Archive &a,  nodetool::alert_condition& ac, const ver_type ver)
    {
      a & ac.alert_mode;
      a & ac.if_build_less_then;
    }

    template <class Archive, class ver_type>
    inline void serialize(Archive &a,  nodetool::maintainers_info& mi, const ver_type ver)
    {
      a & mi.timestamp;
      a & mi.ver_major;
      a & mi.ver_minor;
      a & mi.ver_revision;
      a & mi.build_no;
      a & mi.conditions;
    }

    template <class Archive, class ver_type>
    inline void serialize(Archive &a,  nodetool::maintainers_entry& me, const ver_type ver)
    {
      a & me.maintainers_info_buff;
      a & me.sign;
    }    
  }
}
