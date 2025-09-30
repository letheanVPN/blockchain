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

#include <alloca.h>
#include <assert.h>
#include <stddef.h>
#include <string.h>

#include "hash-ops.h"
#ifdef _M_ARM64
  #include "malloc.h"
#endif 
void tree_hash(const char (*hashes)[HASH_SIZE], size_t count, char *root_hash) {
  assert(count > 0);
  if (count == 1) {
    memcpy(root_hash, hashes, HASH_SIZE);
  } else if (count == 2) {
    cn_fast_hash(hashes, 2 * HASH_SIZE, root_hash);
  } else {
    size_t i, j;
    size_t cnt = count - 1;
    char (*ints)[HASH_SIZE];
    for (i = 1; i < 8 * sizeof(size_t); i <<= 1) {
      cnt |= cnt >> i;
    }
    cnt &= ~(cnt >> 1);
    ints = alloca(cnt * HASH_SIZE);
    memcpy(ints, hashes, (2 * cnt - count) * HASH_SIZE);
    for (i = 2 * cnt - count, j = 2 * cnt - count; j < cnt; i += 2, ++j) {
      cn_fast_hash(hashes[i], 64, ints[j]);
    }
    assert(i == count);
    while (cnt > 2) {
      cnt >>= 1;
      for (i = 0, j = 0; j < cnt; i += 2, ++j) {
        cn_fast_hash(ints[i], 64, ints[j]);
      }
    }
    cn_fast_hash(ints[0], 64, root_hash);
  }
}
