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

#ifndef BlockByHashController_hpp
#define BlockByHashController_hpp

#include "modal/block/details.hpp"
#include "modal/transaction/details.hpp"
#include "controller/ApiCoreInfo.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "rpc/core_rpc_server_commands_defs.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

/**
 *  Block-by-Hash Controller
 */
class BlockByHashController : public oatpp::web::server::api::ApiController {
private:
  OATPP_COMPONENT(std::shared_ptr<ApiCoreInfo>, m_core_info);
public:
  explicit BlockByHashController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:

  ENDPOINT_INFO(getBlockByHash) {
    info->summary = "Get a block by its hash";
    info->addTag("Block");
    info->pathParams["hash"].description = "The hash of the block to retrieve";
    info->addResponse<Object<BlockDetailsModel>>(Status::CODE_200, "application/json");
    info->addResponse(Status::CODE_404, "text/plain");
    info->addResponse(Status::CODE_400, "text/plain");
  }
  ENDPOINT("GET", "/block/{hash}", getBlockByHash, PATH(String, hash)) {

    crypto::hash block_hash{};

    if (!epee::string_tools::hex_to_pod(*hash, block_hash)) {
        return createResponse(Status::CODE_400, "Invalid block hash format");
    }

    currency::block_rpc_extended_info rpc_details;
    if (!m_core_info->getCore().get_blockchain_storage().get_main_block_rpc_details(block_hash, rpc_details)) {
        return createResponse(Status::CODE_404, "Block not found");
    }

    auto blockDetails = BlockDetailsModel::createShared();

    blockDetails->id = rpc_details.id;
    blockDetails->height = rpc_details.height;
    blockDetails->timestamp = rpc_details.timestamp;
    blockDetails->actual_timestamp = rpc_details.actual_timestamp;
    blockDetails->difficulty = rpc_details.difficulty;
    blockDetails->prev_id = rpc_details.prev_id;
    blockDetails->is_orphan = rpc_details.is_orphan;
    blockDetails->base_reward = rpc_details.base_reward;
    blockDetails->summary_reward = rpc_details.summary_reward;
    blockDetails->total_fee = rpc_details.total_fee;
    blockDetails->penalty = rpc_details.penalty;
    blockDetails->already_generated_coins = rpc_details.already_generated_coins;
    blockDetails->block_cumulative_size = rpc_details.block_cumulative_size;
    blockDetails->total_txs_size = rpc_details.total_txs_size;
    blockDetails->cumulative_diff_adjusted = rpc_details.cumulative_diff_adjusted;
    blockDetails->cumulative_diff_precise = rpc_details.cumulative_diff_precise;
    blockDetails->blob = rpc_details.blob;
    blockDetails->miner_text_info = rpc_details.miner_text_info;
    blockDetails->type = rpc_details.type;

    auto tx_details_list = oatpp::List<oatpp::Object<TransactionDetailsModel>>::createShared();
    for(const auto& tx_rpc_info : rpc_details.transactions_details) {
        auto tx_model = TransactionDetailsModel::createShared();
        tx_model->id = tx_rpc_info.id;
        tx_model->fee = tx_rpc_info.fee;
        tx_model->amount = tx_rpc_info.amount;
        tx_model->blob_size = tx_rpc_info.blob_size;
        tx_model->keeper_block = tx_rpc_info.keeper_block;
        tx_model->timestamp = tx_rpc_info.timestamp;
        tx_details_list->push_back(tx_model);
    }
    blockDetails->transactions_details = tx_details_list;

    return createDtoResponse(Status::CODE_200, blockDetails);
  }

};

#include OATPP_CODEGEN_END(ApiController)

#endif /* BlockByHashController_hpp */
