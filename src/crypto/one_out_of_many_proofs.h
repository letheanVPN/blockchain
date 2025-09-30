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
#include "crypto-sugar.h"

namespace crypto
{
  //
  // BGE stands for Bootle, Groth, Esgin
  //
  // This is a proof-of-concept implementation of a log-size one-out-of-many proof based on ideas and approaches by Bootle et al, Groth et al and Esgin et al
  //
  // https://eprint.iacr.org/2014/764
  // https://eprint.iacr.org/2015/643
  // https://eprint.iacr.org/2019/1287
  // 
  // Disclaimer: shouldn't be used in production code until the security proofs and the code are peer-reviewed.
  //

  // m+2 group elements, m(n-1)+2 field elements.
  // Assuming fixed n=4, m = log4(ring_sz) the size is (log4(ring_sz) + 2) group elements and (3*log4(ring_sz) + 2) or, in total, (4*log4(ring_sz) + 4) 32-bytes words

  // ring_sz = m (inputs number)
  // sig_count = k (outputs number)
  // thus:
  // k * (log4(m) + 2) group elements and k * (3*log4(m) + 2) field elements 

  struct BGE_proof
  {
    public_key A;                  // premultiplied by 1/8
    public_key B;                  // premultiplied by 1/8
    std::vector<public_key> Pk;    // premultiplied by 1/8, size = m
    scalar_vec_t f;                // size = m * (n - 1)
    scalar_t y;
    scalar_t z;
  };

  bool generate_BGE_proof(const hash& context_hash, const std::vector<point_t>& ring, const scalar_t& secret, const size_t secret_index, BGE_proof& result, uint8_t* p_err = nullptr);


  bool verify_BGE_proof(const hash& context_hash, const std::vector<const public_key*>& ring, const BGE_proof& sig, uint8_t* p_err = nullptr);


} // namespace crypto
