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

#include "warnings.h"

PUSH_VS_WARNINGS
DISABLE_VS_WARNINGS(4100)
DISABLE_VS_WARNINGS(4503)
#include "serialization/keyvalue_serialization.h"
#include "storages/portable_storage_template_helper.h"
POP_VS_WARNINGS

namespace currency
{
  template<typename t_type>
  struct struct_with_one_t_type
  {
    t_type v;

    BEGIN_KV_SERIALIZE_MAP()
      KV_SERIALIZE(v)
    END_KV_SERIALIZE_MAP()
  };
}
