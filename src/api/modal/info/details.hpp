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

#ifndef InfoModel_hpp
#define InfoModel_hpp

#include "maintainers_info.hpp"
#include "modal/meta/performance.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class InfoModel final : public oatpp::DTO
{
  DTO_INIT(InfoModel, DTO);

  DTO_FIELD(UInt64, height);
  DTO_FIELD(UInt64, tx_count);
  DTO_FIELD(UInt64, tx_pool_size);
  DTO_FIELD(UInt64, alt_blocks_count);
  DTO_FIELD(UInt64, outgoing_connections_count);
  DTO_FIELD(UInt64, incoming_connections_count);
  DTO_FIELD(UInt64, synchronized_connections_count);
  DTO_FIELD(UInt64, white_peerlist_size);
  DTO_FIELD(UInt64, grey_peerlist_size);
  DTO_FIELD(UInt64, current_blocks_median);
  DTO_FIELD(UInt64, alias_count);
  DTO_FIELD(UInt64, current_max_allowed_block_size);
  DTO_FIELD(String, daemon_network_state);
  DTO_FIELD(UInt64, synchronization_start_height);
  DTO_FIELD(UInt64, max_net_seen_height);
  DTO_FIELD(Object<MaintainersInfoModel>, mi);
  DTO_FIELD(Boolean, pos_allowed);
  DTO_FIELD(String, pos_difficulty);
  DTO_FIELD(UInt64, pow_difficulty);
  DTO_FIELD(UInt64, default_fee);
  DTO_FIELD(UInt64, minimum_fee);
  DTO_FIELD(List<Boolean>, is_hardfork_active);
  DTO_FIELD(Int64, net_time_delta_median);
  DTO_FIELD(UInt64, current_network_hashrate_50);
  DTO_FIELD(UInt64, current_network_hashrate_350);
  DTO_FIELD(UInt64, seconds_for_10_blocks);
  DTO_FIELD(UInt64, seconds_for_30_blocks);
  DTO_FIELD(List<UInt64>, transactions_cnt_per_day);
  DTO_FIELD(List<UInt64>, transactions_volume_per_day);
  DTO_FIELD(UInt64, last_pos_timestamp);
  DTO_FIELD(UInt64, last_pow_timestamp);
  DTO_FIELD(String, total_coins);
  DTO_FIELD(UInt64, last_block_size);
  DTO_FIELD(UInt64, tx_count_in_last_block);
  DTO_FIELD(Float64, pos_sequence_factor);
  DTO_FIELD(Float64, pow_sequence_factor);
  DTO_FIELD(UInt64, block_reward);
  DTO_FIELD(UInt64, last_block_total_reward);
  DTO_FIELD(UInt64, pos_diff_total_coins_rate);
  DTO_FIELD(UInt64, last_block_timestamp);
  DTO_FIELD(String, last_block_hash);
  DTO_FIELD(Int64, pos_block_ts_shift_vs_actual);
  DTO_FIELD(Fields<UInt64>, outs_stat); // Represents a map of uint64_t to uint64_t
  DTO_FIELD(Object<PerformanceModel>, performance_data);
  DTO_FIELD(UInt64, offers_count);
  DTO_FIELD(UInt64, expiration_median_timestamp);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* InfoModel_hpp */
