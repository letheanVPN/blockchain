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

#ifndef TxProcessingPerformanceModel_hpp
#define TxProcessingPerformanceModel_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class TxProcessingPerformanceModel final : public oatpp::DTO
{
  DTO_INIT(TxProcessingPerformanceModel, DTO);

  DTO_FIELD(UInt64, tx_check_inputs);
  DTO_FIELD(UInt64, tx_add_one_tx);
  DTO_FIELD(UInt64, tx_process_extra);
  DTO_FIELD(UInt64, tx_process_attachment);
  DTO_FIELD(UInt64, tx_process_inputs);
  DTO_FIELD(UInt64, tx_push_global_index);
  DTO_FIELD(UInt64, tx_check_exist);
  DTO_FIELD(UInt64, tx_print_log);
  DTO_FIELD(UInt64, tx_prapare_append);
  DTO_FIELD(UInt64, tx_append);
  DTO_FIELD(UInt64, tx_append_rl_wait);
  DTO_FIELD(UInt64, tx_append_is_expired);
  DTO_FIELD(UInt64, tx_store_db);
  DTO_FIELD(UInt64, tx_check_inputs_prefix_hash);
  DTO_FIELD(UInt64, tx_check_inputs_attachment_check);
  DTO_FIELD(UInt64, tx_check_inputs_loop);
  DTO_FIELD(UInt64, tx_check_inputs_loop_kimage_check);
  DTO_FIELD(UInt64, tx_check_inputs_loop_ch_in_val_sig);
  DTO_FIELD(UInt64, tx_check_inputs_loop_scan_outputkeys_get_item_size);
  DTO_FIELD(UInt64, tx_check_inputs_loop_scan_outputkeys_relative_to_absolute);
  DTO_FIELD(UInt64, tx_check_inputs_loop_scan_outputkeys_loop);
  DTO_FIELD(UInt64, tx_check_inputs_loop_scan_outputkeys_loop_get_subitem);
  DTO_FIELD(UInt64, tx_check_inputs_loop_scan_outputkeys_loop_find_tx);
  DTO_FIELD(UInt64, tx_check_inputs_loop_scan_outputkeys_loop_handle_output);
  DTO_FIELD(UInt64, tx_mixin_count);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* TxProcessingPerformanceModel_hpp */
