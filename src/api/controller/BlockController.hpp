#ifndef BlockController_hpp
#define BlockController_hpp

#include "../dto/BlockDetailsDto.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

/**
 *  Block Controller
 */
class BlockController : public oatpp::web::server::api::ApiController {
public:
  BlockController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:

  ENDPOINT_INFO(getBlockByHash) {
    info->summary = "Get a block by its hash";
    info->addTag("Block");
    info->pathParams["hash"].description = "The hash of the block to retrieve";
    info->addResponse<Object<BlockDetailsDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/block/{hash}", getBlockByHash, PATH(String, hash)) {
    // TODO: Actually fetch the block from the blockchain core

    auto blockDetails = BlockDetailsDto::createShared();
    blockDetails->actual_timestamp = 1557345925ULL;
    blockDetails->already_generated_coins = "17517253670000000000";
    blockDetails->base_reward = 1000000000000ULL;
    blockDetails->blob = "";
    blockDetails->block_cumulative_size = 6794ULL;
    blockDetails->block_tself_size = 0001ULL;
    blockDetails->cumulative_diff_adjusted = "42413051198";
    blockDetails->cumulative_diff_precise = "28881828324942";
    blockDetails->difficulty = "951296929031";
    blockDetails->effective_fee_median = 01ULL;
    blockDetails->height = 51ULL;
    blockDetails->id = hash; // Use the hash from the path
    blockDetails->is_orphan = false;
    blockDetails->miner_text_info = "";
    blockDetails->object_in_json = "";
    blockDetails->penalty = 0.0f;
    blockDetails->prev_id = "37fe382c755bb8869e4f5255f2aed6a8fb503e195bb4180b65b8e1450b84cafe";
    blockDetails->summary_reward = 1001000000000ULL;
    blockDetails->this_block_fee_median = 1000000000ULL;
    blockDetails->timestamp = 1557345925ULL;
    blockDetails->total_fee = 1000000000ULL;
    blockDetails->total_txs_size = 6794ULL;
    blockDetails->type = 1U;

    auto txDetails = TransactionDetailsDto::createShared();
    txDetails->id = "a6e8da986858e6825fce7a192097e6afae4e889cabe853a9c29b964985b23da8";
    txDetails->fee = 1000000000ULL;
    // ... populate other txDetails fields as needed

    blockDetails->transactions_details = {txDetails};

    return createDtoResponse(Status::CODE_200, blockDetails);
  }

};

#include OATPP_CODEGEN_END(ApiController)

#endif /* BlockController_hpp */
