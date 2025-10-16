// Copyright (c) 2017-2025 Lethean (https://lt.hn)
//
// Licensed under the European Union Public Licence (EUPL) version 1.2.
// You may obtain a copy of the licence at:
//
//     https://joinup.ec.europa.eu/software/page/eupl/licence-eupl
//
// The EUPL is a copyleft licence that is compatible with the MIT/X11
// licence used by the original projects; but maintains OSS status,
// where regional copyright law requires ownership to dictate licence terms.
//
// SPDX‑License‑Identifier: EUPL-1.2
//

#ifndef BlockDetailsDto_hpp
#define BlockDetailsDto_hpp

#include "TransactionDetailsDto.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  DTO for detailed block information.
 */
class BlockDetailsDto : public oatpp::DTO {
  DTO_INIT(BlockDetailsDto, DTO);

  DTO_FIELD(UInt64, actual_timestamp, "actual_timestamp");
  DTO_FIELD(String, already_generated_coins, "already_generated_coins");
  DTO_FIELD(UInt64, base_reward, "base_reward");
  DTO_FIELD(String, blob, "blob");
  DTO_FIELD(UInt64, block_cumulative_size, "block_cumulative_size");
  DTO_FIELD(UInt64, block_tself_size, "block_tself_size");
  DTO_FIELD(String, cumulative_diff_adjusted, "cumulative_diff_adjusted");
  DTO_FIELD(String, cumulative_diff_precise, "cumulative_diff_precise");
  DTO_FIELD(String, difficulty, "difficulty");
  DTO_FIELD(UInt64, effective_fee_median, "effective_fee_median");
  DTO_FIELD(UInt64, height, "height");
  DTO_FIELD(String, id, "id");
  DTO_FIELD(Boolean, is_orphan, "is_orphan");
  DTO_FIELD(String, miner_text_info, "miner_text_info");
  DTO_FIELD(String, object_in_json, "object_in_json");
  DTO_FIELD(UInt64, penalty, "penalty");
  DTO_FIELD(String, pow_seed, "pow_seed");
  DTO_FIELD(String, prev_id, "prev_id");
  DTO_FIELD(UInt64, summary_reward, "summary_reward");
  DTO_FIELD(UInt64, this_block_fee_median, "this_block_fee_median");
  DTO_FIELD(UInt64, timestamp, "timestamp");
  DTO_FIELD(UInt64, total_fee, "total_fee");
  DTO_FIELD(UInt64, total_txs_size, "total_txs_size");
  DTO_FIELD(List<Object<TransactionDetailsDto>>, transactions_details, "transactions_details");
  DTO_FIELD(UInt32, type, "type");
};

#include OATPP_CODEGEN_END(DTO)

#endif /* BlockDetailsDto_hpp */
