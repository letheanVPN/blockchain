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

#include "hash.h"


namespace crypto {

#pragma pack(push, 1)
  POD_CLASS hash160{
    char data[20];
  };
#pragma pack(pop)

  void RIPEMD160_hash(const void *data, size_t length, hash160 &h);
  hash160 RIPEMD160_hash(const void *data, size_t length);
  hash RIPEMD160_hash_256(const void *data, size_t length);

}

POD_MAKE_HASHABLE(crypto, hash160)



