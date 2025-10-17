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

#ifndef BlockProcessingPerformanceModel_hpp
#define BlockProcessingPerformanceModel_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class BlockProcessingPerformanceModel final : public oatpp::DTO
{
  DTO_INIT(BlockProcessingPerformanceModel, DTO);

  DTO_FIELD(UInt64, block_processing_time_0);
  DTO_FIELD(UInt64, block_processing_time_1);
  DTO_FIELD(UInt64, target_calculating_time_2);
  DTO_FIELD(UInt64, longhash_calculating_time_3);
  DTO_FIELD(UInt64, all_txs_insert_time_5);
  DTO_FIELD(UInt64, etc_stuff_6);
  DTO_FIELD(UInt64, insert_time_4);
  DTO_FIELD(UInt64, raise_block_core_event);
  DTO_FIELD(UInt64, validate_miner_transaction_time);
  DTO_FIELD(UInt64, collect_rangeproofs_data_from_tx_time);
  DTO_FIELD(UInt64, verify_multiple_zc_outs_range_proofs_time);
  DTO_FIELD(UInt64, target_calculating_enum_blocks);
  DTO_FIELD(UInt64, target_calculating_calc);
  DTO_FIELD(UInt64, pos_validate_ki_search);
  DTO_FIELD(UInt64, pos_validate_get_out_keys_for_inputs);
  DTO_FIELD(UInt64, pos_validate_zvp);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* BlockProcessingPerformanceModel_hpp */
