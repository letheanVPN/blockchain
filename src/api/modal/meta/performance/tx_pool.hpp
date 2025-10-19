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

#ifndef TxPoolPerformanceModel_hpp
#define TxPoolPerformanceModel_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class TxPoolPerformanceModel final : public oatpp::DTO
{
  DTO_INIT(TxPoolPerformanceModel, DTO);

  DTO_FIELD(UInt64, tx_processing_time);
  DTO_FIELD(UInt64, check_inputs_types_supported_time);
  DTO_FIELD(UInt64, expiration_validate_time);
  DTO_FIELD(UInt64, validate_amount_time);
  DTO_FIELD(UInt64, validate_alias_time);
  DTO_FIELD(UInt64, check_keyimages_ws_ms_time);
  DTO_FIELD(UInt64, check_inputs_time);
  DTO_FIELD(UInt64, begin_tx_time);
  DTO_FIELD(UInt64, update_db_time);
  DTO_FIELD(UInt64, db_commit_time);
  DTO_FIELD(UInt64, check_post_hf4_balance);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* TxPoolPerformanceModel_hpp */
