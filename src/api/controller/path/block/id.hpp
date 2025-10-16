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

#ifndef BlockByIdController_hpp
#define BlockByIdController_hpp

#include "dto/BlockDetailsDto.hpp"
#include "dto/TransactionDetailsDto.hpp"
#include "controller/ApiCoreInfoComponent.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "rpc/core_rpc_server_commands_defs.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

/**
 *  Block-by-ID Controller
 */
class BlockByIdController : public oatpp::web::server::api::ApiController {
private:
  OATPP_COMPONENT(std::shared_ptr<ApiCoreInfoComponent>, m_core_info);
public:
  explicit BlockByIdController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:

  ENDPOINT_INFO(getBlockById) {
    info->summary = "Get a block by its ID (height)";
    info->addTag("Block");
    info->pathParams["id"].description = "The ID (height) of the block to retrieve";
    info->addResponse<Object<BlockDetailsDto>>(Status::CODE_200, "application/json");
    info->addResponse(Status::CODE_404, "text/plain");
  }
  ENDPOINT("GET", "/block/id/{id}", getBlockById, PATH(UInt64, id)) {

    currency::block_rpc_extended_info rpc_details;
    if (!m_core_info->getCore().get_blockchain_storage().get_main_block_rpc_details(id, rpc_details)) {
        return createResponse(Status::CODE_404, "Block not found");
    }

    auto blockDetails = BlockDetailsDto::createShared();

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

    auto tx_details_list = oatpp::List<oatpp::Object<TransactionDetailsDto>>::createShared();
    for(const auto& tx_rpc_info : rpc_details.transactions_details) {
        auto tx_dto = TransactionDetailsDto::createShared();
        tx_dto->id = tx_rpc_info.id;
        tx_dto->fee = tx_rpc_info.fee;
        tx_dto->amount = tx_rpc_info.amount;
        tx_dto->blob_size = tx_rpc_info.blob_size;
        tx_dto->keeper_block = tx_rpc_info.keeper_block;
        tx_dto->timestamp = tx_rpc_info.timestamp;
        tx_details_list->push_back(tx_dto);
    }
    blockDetails->transactions_details = tx_details_list;

    return createDtoResponse(Status::CODE_200, blockDetails);
  }

};

#include OATPP_CODEGEN_END(ApiController)

#endif /* BlockByIdController_hpp */
