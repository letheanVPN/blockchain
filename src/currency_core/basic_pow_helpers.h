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

#include <typeindex>
#include <unordered_set>
#include <unordered_map>

#include "account.h"
#include "include_base_utils.h"

#include "currency_format_utils_abstract.h"
#include "common/crypto_stream_operators.h"
#include "currency_protocol/currency_protocol_defs.h"
#include "crypto/crypto.h"
#include "crypto/hash.h"
#include "difficulty.h"
//#include "offers_services_helpers.h"
#include "rpc/core_rpc_server_commands_defs.h"
#include "bc_payments_id_service.h"
#include "bc_attachments_helpers_basic.h"
#include "blockchain_storage_basic.h"

#define CURRENCY_MINER_BLOCK_BLOB_NONCE_OFFSET    1

namespace currency
{
  int ethash_height_to_epoch(uint64_t height);
  crypto::hash ethash_epoch_to_seed(int epoch);
  crypto::hash get_block_header_mining_hash(const block& b);
  crypto::hash get_block_longhash(uint64_t h, const crypto::hash& block_header_hash, uint64_t nonce);
  void get_block_longhash(const block& b, crypto::hash& res);
  crypto::hash get_block_longhash(const block& b);

  inline uint64_t get_nonce_from_blockblob(const blobdata& bd)
  {
    uint64_t nonce = 0;
    CHECK_AND_ASSERT_MES(bd.size() >= CURRENCY_MINER_BLOCK_BLOB_NONCE_OFFSET + sizeof(nonce), 0, "Unexpected block buffer size = " << bd.size());
    std::memcpy(&nonce, &bd[CURRENCY_MINER_BLOCK_BLOB_NONCE_OFFSET], sizeof(nonce));
    return nonce;
  }

  inline void set_nonce_to_blockblob(blobdata& bd, const uint64_t nonce)
  {
    CHECK_AND_ASSERT_MES(bd.size() >= CURRENCY_MINER_BLOCK_BLOB_NONCE_OFFSET + sizeof(nonce), void(), "Unexpected block buffer size = " << bd.size());
    std::memcpy(&bd[CURRENCY_MINER_BLOCK_BLOB_NONCE_OFFSET], &nonce, sizeof(nonce));
  }
}