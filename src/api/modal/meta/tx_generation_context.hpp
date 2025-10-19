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

#ifndef TxGenerationContextModel_hpp
#define TxGenerationContextModel_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class TxGenerationContextModel final : public oatpp::DTO
{
  DTO_INIT(TxGenerationContextModel, DTO);

  DTO_FIELD(List<String>, asset_ids);
  DTO_FIELD(List<String>, blinded_asset_ids);
  DTO_FIELD(List<String>, amount_commitments);
  DTO_FIELD(List<String>, asset_id_blinding_masks);
  DTO_FIELD(List<String>, amounts);
  DTO_FIELD(List<String>, amount_blinding_masks);
  DTO_FIELD(List<String>, pseudo_outs_blinded_asset_ids);
  DTO_FIELD(List<String>, pseudo_outs_plus_real_out_blinding_masks);
  DTO_FIELD(List<String>, real_zc_ins_asset_ids);
  DTO_FIELD(List<UInt64>, zc_input_amounts);
  DTO_FIELD(String, pseudo_out_amount_commitments_sum);
  DTO_FIELD(String, pseudo_out_amount_blinding_masks_sum);
  DTO_FIELD(String, real_in_asset_id_blinding_mask_x_amount_sum);
  DTO_FIELD(String, amount_commitments_sum);
  DTO_FIELD(String, amount_blinding_masks_sum);
  DTO_FIELD(String, asset_id_blinding_mask_x_amount_sum);
  DTO_FIELD(String, ao_asset_id);
  DTO_FIELD(String, ao_asset_id_pt);
  DTO_FIELD(String, ao_amount_commitment);
  DTO_FIELD(String, ao_amount_blinding_mask);
  DTO_FIELD(Boolean, ao_commitment_in_outputs);
  DTO_FIELD(String, tx_key_pub);
  DTO_FIELD(String, tx_key_sec);
  DTO_FIELD(String, tx_pub_key_p);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* TxGenerationContextModel_hpp */
