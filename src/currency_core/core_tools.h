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

#include <algorithm>
#include "blockchain_storage.h"
#include "bc_offers_service.h"

namespace currency
{
  inline
  bool resync_market(blockchain_storage& bcs, bc_services::bc_offers_service& offers_service)
  {
    offers_service.clear();
    uint64_t top_block_height = bcs.get_top_block_height();
    currency::block b = AUTO_VAL_INIT(b);
    bcs.get_top_block(b);
    uint64_t start_height = bcs.get_block_h_older_then(b.timestamp - OFFER_MAXIMUM_LIFE_TIME);
    uint64_t print_height_interval = std::max((top_block_height - start_height) / 10ull + 1, 10ull), next_print_height = start_height + print_height_interval;
    LOG_PRINT_MAGENTA("Resynchronizing market from height " << start_height << " to height " << top_block_height, LOG_LEVEL_0);
    for (uint64_t i = start_height; i <= top_block_height; i++)
    {
      if (i == next_print_height)
      {
        LOG_PRINT_MAGENTA("Resynchronizing market: height " << i << " of " << top_block_height << " (" << ((i - start_height) * 100 / (top_block_height - start_height)) << "%)", LOG_LEVEL_0);
        next_print_height += print_height_interval;
      }

      bcs.get_block_by_height(i, b);
      crypto::hash block_id = get_block_hash(b);
      for (auto tx_id : b.tx_hashes)
      {
        auto tx_ptr = bcs.get_tx(tx_id);
        CHECK_AND_ASSERT_MES(tx_ptr, false, "Internal error: Failed to get transaction " << tx_id << "from block[" << i << "]");
        uint64_t count = 0;
        for (const auto& at : tx_ptr->attachment)
        {
          if (at.type() == typeid(currency::tx_service_attachment))
          {
            const currency::tx_service_attachment& tsa = boost::get<currency::tx_service_attachment>(at);
            if (tsa.service_id == BC_OFFERS_SERVICE_ID)
            {
              static_cast<currency::i_bc_service*>(&offers_service)->handle_entry_push(tsa, count, *tx_ptr, i, block_id, b.timestamp); //handle service
            }
            ++count;
          }
        }
      }
    }
    LOG_PRINT_MAGENTA("Resynchronizing market finished.", LOG_LEVEL_0);
    return true;
  }
}