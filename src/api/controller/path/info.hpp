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

#ifndef InfoController_hpp
#define InfoController_hpp

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "controller/ApiCoreInfo.hpp"
#include "modal/info/details.hpp"
#include "currency_core/currency_stat_info.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

/**
 *  Info Controller
 */
class InfoController : public oatpp::web::server::api::ApiController {
private:
    OATPP_COMPONENT(std::shared_ptr<ApiCoreInfo>, m_core_info);
public:
  explicit InfoController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:

  ENDPOINT_INFO(getInfo) {
    info->summary = "Get detailed information about the blockchain and daemon state";
    info->addTag("Info");
    info->addResponse<Object<InfoModel>>(Status::CODE_200, "application/json");
    info->queryParams["flags"].name = "flags";
    info->queryParams["flags"].description = "Possible values: net_time_delta_median, current_network_hashrate_50, current_network_hashrate_350, seconds_for_10_blocks, seconds_for_30_blocks, transactions_daily_stat, last_pos_timestamp, last_pow_timestamp, total_coins, last_block_size, tx_count_in_last_block, pos_sequence_factor, pow_sequence_factor, pos_difficulty, performance, outs_stat, expirations_median.";
  }
  ENDPOINT("GET", "/info", getInfo, QUERY(String, flags, "flags",""), QUERIES(QueryParams, queryParams)) {
    auto model = InfoModel::createShared();
    currency::core& core = m_core_info->getCore();
    currency::t_currency_protocol_handler<currency::core>& p2p_handler = m_core_info->getP2p().get_payload_object();
    currency::blockchain_storage& bcs = core.get_blockchain_storage();

    model->height = bcs.get_current_blockchain_size();
    model->tx_count = bcs.get_total_transactions() - model->height; //without coinbase
    model->tx_pool_size = core.get_pool_transactions_count();
    model->alt_blocks_count = bcs.get_alternative_blocks_count();
    uint64_t total_conn = m_core_info->getP2p().get_connections_count();
    model->outgoing_connections_count = m_core_info->getP2p().get_outgoing_connections_count();
    model->incoming_connections_count = total_conn - model->outgoing_connections_count;
    model->synchronized_connections_count = p2p_handler.get_synchronized_connections_count();
    model->white_peerlist_size = m_core_info->getP2p().get_peerlist_manager().get_white_peers_count();
    model->grey_peerlist_size = m_core_info->getP2p().get_peerlist_manager().get_gray_peers_count();
    model->current_blocks_median = bcs.get_current_comulative_blocksize_limit() / 2;
    model->alias_count = bcs.get_aliases_count();
    model->current_max_allowed_block_size = bcs.get_current_comulative_blocksize_limit();

    if (!model->outgoing_connections_count)
        model->daemon_network_state = "connecting";
    else if (p2p_handler.is_synchronized())
        model->daemon_network_state = "online";
    else
        model->daemon_network_state = "synchronizing";

    model->synchronization_start_height = p2p_handler.get_core_inital_height();
    model->max_net_seen_height = p2p_handler.get_max_seen_height();
    
    nodetool::maintainers_info_external mi_res;
    m_core_info->getP2p().get_maintainers_info(mi_res);
    auto mi_model = MaintainersInfoModel::createShared();
    mi_model->ver_major = mi_res.ver_major;
    mi_model->ver_minor = mi_res.ver_minor;
    mi_model->ver_revision = mi_res.ver_revision;
    mi_model->build_no = mi_res.build_no;
    mi_model->mode = mi_res.mode;
    model->mi = mi_model;

    model->pos_allowed = bcs.is_pos_allowed();
    model->pos_difficulty = bcs.get_cached_next_difficulty(true).convert_to<std::string>();
    model->pow_difficulty = bcs.get_cached_next_difficulty(false).convert_to<uint64_t>();
    model->default_fee = bcs.get_core_runtime_config().tx_default_fee;
    model->minimum_fee = bcs.get_core_runtime_config().tx_pool_min_fee;

    auto hf_list = oatpp::List<Boolean>::createShared();
    for (size_t i = 0; i != ZANO_HARDFORKS_TOTAL; i++)
    {
        hf_list->push_back(bcs.is_hardfork_active(i));
    }
    model->is_hardfork_active = hf_list;

    auto flagsStr = queryParams.get("flags");
    if (flagsStr) {
        std::istringstream iss(flagsStr->c_str());
        std::string flag;
        while (std::getline(iss, flag, ',')) {
            if (flag == "net_time_delta_median") {
                int64_t last_median2local_time_diff, last_ntp2local_time_diff;
                if (!p2p_handler.get_last_time_sync_difference(last_median2local_time_diff, last_ntp2local_time_diff))
                    model->net_time_delta_median = 1;
            } else if (flag == "current_network_hashrate_50") {
                model->current_network_hashrate_50 = bcs.get_current_hashrate(50);
            } else if (flag == "current_network_hashrate_350") {
                model->current_network_hashrate_350 = bcs.get_current_hashrate(350);
            } else if (flag == "seconds_for_10_blocks") {
                model->seconds_for_10_blocks = bcs.get_seconds_between_last_n_block(10);
            } else if (flag == "seconds_for_30_blocks") {
                model->seconds_for_30_blocks = bcs.get_seconds_between_last_n_block(30);
            } else if (flag == "transactions_daily_stat") {
                uint64_t daily_tx_count = 0, daily_tx_vol = 0;
                bcs.get_transactions_daily_stat(daily_tx_count, daily_tx_vol);
                auto daily_tx_count_list = oatpp::List<UInt64>::createShared();
                daily_tx_count_list->push_back(daily_tx_count);
                model->transactions_cnt_per_day = daily_tx_count_list;
                auto daily_tx_vol_list = oatpp::List<UInt64>::createShared();
                daily_tx_vol_list->push_back(daily_tx_vol);
                model->transactions_volume_per_day = daily_tx_vol_list;
            } else if (flag == "last_pos_timestamp") {
                auto pos_bl_ptr = bcs.get_last_block_of_type(true);
                if (pos_bl_ptr) model->last_pos_timestamp = pos_bl_ptr->bl.timestamp;
            } else if (flag == "last_pow_timestamp") {
                auto pow_bl_ptr = bcs.get_last_block_of_type(false);
                if (pow_bl_ptr) model->last_pow_timestamp = pow_bl_ptr->bl.timestamp;
            } else if (flag == "total_coins") {
                model->total_coins = boost::lexical_cast<std::string>(bcs.total_coins());
            } else if (flag == "last_block_size") {
                std::vector<size_t> sz;
                bcs.get_last_n_blocks_sizes(sz, 1);
                model->last_block_size = sz.size() ? sz.back() : 0;
            } else if (flag == "tx_count_in_last_block") {
                currency::block b = AUTO_VAL_INIT(b);
                bcs.get_top_block(b);
                model->tx_count_in_last_block = b.tx_hashes.size();
            } else if (flag == "pos_sequence_factor") {
                model->pos_sequence_factor = bcs.get_current_sequence_factor(true);
            } else if (flag == "pow_sequence_factor") {
                model->pow_sequence_factor = bcs.get_current_sequence_factor(false);
            } else if (flag == "pos_difficulty") {
                currency::block b = AUTO_VAL_INIT(b);
                bcs.get_top_block(b);
                model->block_reward = currency::get_base_block_reward(model->height);
                model->last_block_total_reward = currency::get_reward_from_miner_tx(b.miner_tx);
                model->pos_diff_total_coins_rate = (bcs.get_cached_next_difficulty(true) / (bcs.total_coins() - PREMINE_AMOUNT + 1)).convert_to<uint64_t>();
                model->last_block_timestamp = b.timestamp;
                model->last_block_hash = string_tools::pod_to_hex(get_block_hash(b));
            } else if (flag == "performance") {
                auto perf_model = PerformanceModel::createShared();
                const currency::blockchain_storage::performnce_data& pd = bcs.get_performnce_data();
                auto block_processing_model = BlockProcessingPerformanceModel::createShared();
                block_processing_model->block_processing_time_0 = pd.block_processing_time_0_ms.get_avg();
                block_processing_model->block_processing_time_1 = pd.block_processing_time_1.get_avg();
                block_processing_model->target_calculating_time_2 = pd.target_calculating_time_2.get_avg();
                block_processing_model->longhash_calculating_time_3 = pd.longhash_calculating_time_3.get_avg();
                block_processing_model->all_txs_insert_time_5 = pd.all_txs_insert_time_5.get_avg();
                block_processing_model->etc_stuff_6 = pd.etc_stuff_6.get_avg();
                block_processing_model->insert_time_4 = pd.insert_time_4.get_avg();
                block_processing_model->raise_block_core_event = pd.raise_block_core_event.get_avg();
                block_processing_model->target_calculating_enum_blocks = pd.target_calculating_enum_blocks.get_avg();
                block_processing_model->target_calculating_calc = pd.target_calculating_calc.get_avg();
                perf_model->block_processing = block_processing_model;

                auto tx_processing_model = TxProcessingPerformanceModel::createShared();
                tx_processing_model->tx_check_inputs = pd.tx_check_inputs_time.get_avg();
                tx_processing_model->tx_add_one_tx = pd.tx_add_one_tx_time.get_avg();
                tx_processing_model->tx_process_extra = pd.tx_process_extra.get_avg();
                tx_processing_model->tx_process_attachment = pd.tx_process_attachment.get_avg();
                tx_processing_model->tx_process_inputs = pd.tx_process_inputs.get_avg();
                tx_processing_model->tx_push_global_index = pd.tx_push_global_index.get_avg();
                tx_processing_model->tx_check_exist = pd.tx_check_exist.get_avg();
                tx_processing_model->tx_append = pd.tx_append_time.get_avg();
                tx_processing_model->tx_append_rl_wait = pd.tx_append_rl_wait.get_avg();
                tx_processing_model->tx_append_is_expired = pd.tx_append_is_expired.get_avg();
                tx_processing_model->tx_store_db = pd.tx_store_db.get_avg();
                tx_processing_model->tx_check_inputs_prefix_hash = pd.tx_check_inputs_prefix_hash.get_avg();
                tx_processing_model->tx_check_inputs_attachment_check = pd.tx_check_inputs_attachment_check.get_avg();
                tx_processing_model->tx_check_inputs_loop = pd.tx_check_inputs_loop.get_avg();
                tx_processing_model->tx_check_inputs_loop_kimage_check = pd.tx_check_inputs_loop_kimage_check.get_avg();
                tx_processing_model->tx_check_inputs_loop_ch_in_val_sig = pd.tx_check_inputs_loop_ch_in_val_sig.get_avg();
                tx_processing_model->tx_check_inputs_loop_scan_outputkeys_get_item_size = pd.tx_check_inputs_loop_scan_outputkeys_get_item_size.get_avg();
                tx_processing_model->tx_check_inputs_loop_scan_outputkeys_relative_to_absolute = pd.tx_check_inputs_loop_scan_outputkeys_relative_to_absolute.get_avg();
                tx_processing_model->tx_check_inputs_loop_scan_outputkeys_loop = pd.tx_check_inputs_loop_scan_outputkeys_loop.get_avg();
                tx_processing_model->tx_check_inputs_loop_scan_outputkeys_loop_get_subitem = pd.tx_check_inputs_loop_scan_outputkeys_loop_get_subitem.get_avg();
                tx_processing_model->tx_check_inputs_loop_scan_outputkeys_loop_find_tx = pd.tx_check_inputs_loop_scan_outputkeys_loop_find_tx.get_avg();
                tx_processing_model->tx_check_inputs_loop_scan_outputkeys_loop_handle_output = pd.tx_check_inputs_loop_scan_outputkeys_loop_handle_output.get_avg();
                tx_processing_model->tx_mixin_count = pd.tx_mixin_count.get_avg();
                perf_model->tx_processing = tx_processing_model;

                const currency::tx_memory_pool::performnce_data& pool_pd = core.get_tx_pool().get_performnce_data();
                auto tx_pool_model = TxPoolPerformanceModel::createShared();
                tx_pool_model->tx_processing_time = pool_pd.tx_processing_time.get_avg();
                tx_pool_model->check_inputs_types_supported_time = pool_pd.check_inputs_types_supported_time.get_avg();
                tx_pool_model->expiration_validate_time = pool_pd.expiration_validate_time.get_avg();
                tx_pool_model->validate_amount_time = pool_pd.validate_amount_time.get_avg();
                tx_pool_model->validate_alias_time = pool_pd.validate_alias_time.get_avg();
                tx_pool_model->check_keyimages_ws_ms_time = pool_pd.check_keyimages_ws_ms_time.get_avg();
                tx_pool_model->check_inputs_time = pool_pd.check_inputs_time.get_avg();
                tx_pool_model->begin_tx_time = pool_pd.begin_tx_time.get_avg();
                tx_pool_model->update_db_time = pool_pd.update_db_time.get_avg();
                tx_pool_model->db_commit_time = pool_pd.db_commit_time.get_avg();
                perf_model->tx_pool = tx_pool_model;

                auto db_stat_model = DbStatInfoModel::createShared();
                db_stat_model->map_size = pd.si.map_size;
                db_stat_model->tx_count = pd.si.tx_count;
                db_stat_model->write_tx_count = pd.si.write_tx_count;
                perf_model->db_stat_info = db_stat_model;

                model->performance_data = perf_model;
            } else if (flag == "expirations_median") {
                model->expiration_median_timestamp = bcs.get_tx_expiration_median();
            }
        }
    }

    return createDtoResponse(Status::CODE_200, model);
  }

};

#include OATPP_CODEGEN_END(ApiController)

#endif /* InfoController_hpp */
