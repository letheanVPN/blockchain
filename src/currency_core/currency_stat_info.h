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
#include "serialization/keyvalue_serialization.h"


namespace currency
{

  struct chain_entry
  {
    uint64_t h;
    std::string id;
    BEGIN_KV_SERIALIZE_MAP()
      KV_SERIALIZE(h)
      KV_SERIALIZE(id)
    END_KV_SERIALIZE_MAP()
  };


  struct error_stat_entry
  {
    std::string channel;
    uint64_t err_count;

    BEGIN_KV_SERIALIZE_MAP()
      KV_SERIALIZE(channel)
      KV_SERIALIZE(err_count)
    END_KV_SERIALIZE_MAP()
  };

  struct core_stat_info
  {
    struct params
    {
      uint64_t chain_len;
      uint64_t logs_journal_len;
      BEGIN_KV_SERIALIZE_MAP()
        KV_SERIALIZE(chain_len)
        KV_SERIALIZE(logs_journal_len)
      END_KV_SERIALIZE_MAP()
    };

    uint64_t tx_pool_size;
    uint64_t blockchain_height;
    uint64_t mining_speed;
    uint64_t alternative_blocks;
    bool epic_failure_happend;
    std::string top_block_id_str;
    std::list<chain_entry> main_chain_blocks;
    std::list<chain_entry> alt_chain_blocks;
    std::list<error_stat_entry> errors_stat;
    std::list<std::string> errors_journal;
    
    BEGIN_KV_SERIALIZE_MAP()
      KV_SERIALIZE(tx_pool_size)
      KV_SERIALIZE(blockchain_height)
      KV_SERIALIZE(mining_speed)
      KV_SERIALIZE(alternative_blocks)
      KV_SERIALIZE(main_chain_blocks)
      KV_SERIALIZE(top_block_id_str)
      //KV_SERIALIZE(alt_chain_blocks)
      KV_SERIALIZE(errors_stat)
      KV_SERIALIZE(epic_failure_happend)
      KV_SERIALIZE(errors_journal)
    END_KV_SERIALIZE_MAP()
  };
}
