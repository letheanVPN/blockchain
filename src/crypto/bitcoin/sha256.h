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

#ifndef BITCOIN_CRYPTO_SHA256_H
#define BITCOIN_CRYPTO_SHA256_H

#include <stdint.h>
#include <stdlib.h>
#include <string>

/** A hasher class for SHA-256. */
class CSHA256
{
private:
  uint32_t s[8];
  unsigned char buf[64];
  uint64_t bytes;

public:
  static const size_t OUTPUT_SIZE = 32;

  CSHA256();
  CSHA256& Write(const unsigned char* data, size_t len);
  void Finalize(unsigned char hash[OUTPUT_SIZE]);
  CSHA256& Reset();
};

/** Autodetect the best available SHA256 implementation.
*  Returns the name of the implementation.
*/
std::string SHA256AutoDetect();

/** Compute multiple double-SHA256's of 64-byte blobs.
*  output:  pointer to a blocks*32 byte output buffer
*  input:   pointer to a blocks*64 byte input buffer
*  blocks:  the number of hashes to compute.
*/
void SHA256D64(unsigned char* output, const unsigned char* input, size_t blocks);

#endif // BITCOIN_CRYPTO_SHA256_H