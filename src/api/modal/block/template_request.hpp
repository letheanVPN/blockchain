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

#ifndef BlockTemplateRequestModel_hpp
#define BlockTemplateRequestModel_hpp

#include "../meta/pos_entry.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class BlockTemplateRequestModel final : public oatpp::DTO
{
  DTO_INIT(BlockTemplateRequestModel, DTO);

  DTO_FIELD(String, miner_address);
  DTO_FIELD(String, stakeholder_address);
  DTO_FIELD(String, ex_nonce);
  DTO_FIELD(Boolean, pos, "pos_block");
  DTO_FIELD(Boolean, ignore_pow_ts_check);
  DTO_FIELD(Object<PosEntryModel>, pe);
  DTO_FIELD(List<String>, explicit_txs);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* BlockTemplateRequestModel_hpp */
