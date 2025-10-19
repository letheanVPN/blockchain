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

#ifndef BlockTemplateModel_hpp
#define BlockTemplateModel_hpp

#include "../meta/tx_generation_context.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class BlockTemplateModel final : public oatpp::DTO
{
  DTO_INIT(BlockTemplateModel, DTO);

  DTO_FIELD(String, blocktemplate_blob);
  DTO_FIELD(String, difficulty);
  DTO_FIELD(UInt64, height);
  DTO_FIELD(Object<TxGenerationContextModel>, miner_tx_tgc);
  DTO_FIELD(UInt64, block_reward_without_fee);
  DTO_FIELD(UInt64, block_reward);
  DTO_FIELD(UInt64, txs_fee);
  DTO_FIELD(String, prev_hash);
  DTO_FIELD(String, seed);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* BlockTemplateModel_hpp */
