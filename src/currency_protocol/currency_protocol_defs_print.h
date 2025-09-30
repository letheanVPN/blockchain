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

#include "currency_core/currency_format_utils_abstract.h"
#include "currency_core/currency_format_utils_blocks.h"
#include "storages/portable_storage_to_json.h"

namespace currency
{
  //------------------------------------------------------------------------------------------------------------------------
  inline std::string print_complete_block_entry_list(const std::list<block_complete_entry>& blocks)
  {
    std::stringstream ss;
    size_t i = 0;
    for (const block_complete_entry& block_entry : blocks)
    {
      ss << "[" << i << "]";
      block b = AUTO_VAL_INIT(b);
      if (!parse_and_validate_object_from_blob(block_entry.block, b))
      {
        ss << "UNPARSED" << ENDL;
      }
      ss << get_block_hash(b) << "{....parent: " << b.prev_id << "....}" << ENDL;

      i++;
    }
    return ss.str();
  }

  template<typename container_t>
  std::string print_container_of_hashs(const container_t& cont, size_t indent)
  {
    std::stringstream ss;
    std::string indent_str(indent, ' ');
    for (const auto& h : cont)
    {
      ss << indent_str << h << ENDL;
    }
    return ss.str();
  }

  inline
    std::string print_kv_structure(const NOTIFY_REQUEST_GET_OBJECTS::request& v)
  {
    std::stringstream ss;
    ss << "blocks: {" << ENDL << print_container_of_hashs(v.blocks, 2) << ENDL << "}";
    ss << "txs: {" << ENDL << print_container_of_hashs(v.txs, 2) << ENDL << "}";
    return ss.str();
  }

  inline
    std::string print_kv_structure(const NOTIFY_RESPONSE_GET_OBJECTS::request& v)
  {
    std::stringstream ss;
    ss << "\"blocks\":{" << ENDL << print_complete_block_entry_list(v.blocks) << ENDL << "}, " << ENDL;
    ss << "\"missed_ids\":" << ENDL;
    ::epee::serialization::recursive_visitor<::epee::serialization::strategy_json>::dump_as_(ss, v.missed_ids, 2);
    ss << ENDL << "\"current_blockchain_height\":" << v.current_blockchain_height;
    return ss.str();
  }

  inline
    std::string print_kv_structure(const NOTIFY_REQUEST_CHAIN::request& v)
  {
    std::stringstream ss;
    ss << "block_ids: {" << ENDL << print_container_of_hashs(v.block_ids, 2) << ENDL << "}";
    return ss.str();
  }
  inline
    std::string print_kv_structure(const NOTIFY_RESPONSE_CHAIN_ENTRY::request& v)
  {
    std::stringstream ss;
    ss << "start_height:" << v.start_height << ENDL;
    ss << "total_height:" << v.total_height << ENDL;
    ss << "block_ids: {" << ENDL;
    for (const block_context_info& bei : v.m_block_ids)
    {
      ss << bei.h << ":" << bei.cumul_size << ENDL;
    }
    ss << "}";
    return ss.str();
  }


}