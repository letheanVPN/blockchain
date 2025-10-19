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

#ifndef BlockController_hpp
#define BlockController_hpp

#include "modal/block/details.hpp"
#include "modal/transaction/details.hpp"
#include "controller/ApiCoreInfo.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include "rpc/core_rpc_server_commands_defs.h"
#include <string>

#include OATPP_CODEGEN_BEGIN(ApiController)

/**
 *  Block Controller
 *  Retrieves one or more blocks with optional pagination.
 */
class BlockController : public oatpp::web::server::api::ApiController {
private:
  OATPP_COMPONENT(std::shared_ptr<ApiCoreInfo>, m_core_info);

  // Helper function to populate a block details model from RPC details
  oatpp::Object<BlockDetailsModel> populateBlockDetailsModel(const currency::block_rpc_extended_info& rpc_details) {
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
    return blockDetails;
  }

public:
  explicit BlockController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:

  ENDPOINT_INFO(getBlocks) {
    info->summary = "Get one or more blocks, with optional pagination.";
    info->addTag("Block");
    info->queryParams["limit"].description = "Number of blocks to retrieve. Default is 1. If limit is 1, a single block object is returned. Otherwise, a list of blocks is returned.";
    info->queryParams["offset"].description = "Number of blocks to skip from the start height. Default is 0.";
    info->queryParams["start"].description = "The starting block height. If not provided, the current top block height is used.";
    info->addResponse<Object<BlockDetailsModel>>(Status::CODE_200, "application/json", "A single block object.");
    info->addResponse<List<Object<BlockDetailsModel>>>(Status::CODE_200, "application/json", "A list of block objects.");
    info->addResponse(Status::CODE_404, "text/plain");
    info->addResponse(Status::CODE_400, "text/plain");
  }
  ENDPOINT("GET", "/block", getBlocks, QUERIES(QueryParams, queryParams)) {
    const auto limitStr = queryParams.get("limit");
    const auto offsetStr = queryParams.get("offset");
    const auto startStr = queryParams.get("start");

    uint64_t limit = 1;
    if (limitStr) {
        try {
            limit = std::stoull(limitStr->c_str());
        } catch (const std::exception& e) {
            return createResponse(Status::CODE_400, "Invalid 'limit' parameter");
        }
    }

    uint64_t offset = 0;
    if (offsetStr) {
        try {
            offset = std::stoull(offsetStr->c_str());
        } catch (const std::exception& e) {
            return createResponse(Status::CODE_400, "Invalid 'offset' parameter");
        }
    }

    uint64_t start_height;
    if (startStr) {
        try {
            start_height = std::stoull(startStr->c_str());
        } catch (const std::exception& e) {
            return createResponse(Status::CODE_400, "Invalid 'start' parameter");
        }
    } else {
        start_height = m_core_info->getCore().get_blockchain_storage().get_current_blockchain_size() - 1;
    }
    
    if (limit == 0) {
        return createResponse(Status::CODE_400, "'limit' must be greater than 0");
    }

    if (start_height < offset) {
        return createResponse(Status::CODE_400, "'start' height cannot be less than 'offset'");
    }

    uint64_t current_height = start_height - offset;

    if (limit == 1) {
        currency::block_rpc_extended_info rpc_details;
        if (!m_core_info->getCore().get_blockchain_storage().get_main_block_rpc_details(current_height, rpc_details)) {
            return createResponse(Status::CODE_404, "Block not found at specified height");
        }
        return createDtoResponse(Status::CODE_200, populateBlockDetailsModel(rpc_details));
    }

    auto block_list = oatpp::List<oatpp::Object<BlockDetailsModel>>::createShared();
    for(uint64_t i = 0; i < limit; ++i)
    {
      if(current_height < i)
      {
        break;  // Reached genesis
      }
      uint64_t height_to_fetch = current_height - i;
      currency::block_rpc_extended_info rpc_details;
      if(m_core_info->getCore().get_blockchain_storage().get_main_block_rpc_details(height_to_fetch, rpc_details))
      {
        block_list->push_back(populateBlockDetailsModel(rpc_details));
      }
      else
      {
        // Could be that we requested past genesis, or a block is missing for some reason.
        // We'll just stop here.
        break;
      }
    }
    return createDtoResponse(Status::CODE_200, block_list);
  }

};

#include OATPP_CODEGEN_END(ApiController)

#endif /* BlockController_hpp */
