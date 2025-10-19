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

#ifndef PosEntryModel_hpp
#define PosEntryModel_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class PosEntryModel final : public oatpp::DTO
{
  DTO_INIT(PosEntryModel, DTO);

  DTO_FIELD(UInt64, amount);
  DTO_FIELD(UInt64, g_index);
  DTO_FIELD(String, keyimage);
  DTO_FIELD(UInt64, block_timestamp);
  DTO_FIELD(UInt64, stake_unlock_time);
  DTO_FIELD(String, tx_id);
  DTO_FIELD(UInt64, tx_out_index);
  DTO_FIELD(UInt64, wallet_index);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* PosEntryModel_hpp */
