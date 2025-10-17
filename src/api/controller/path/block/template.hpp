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

#ifndef BlockTemplateController_hpp
#define BlockTemplateController_hpp

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "controller/ApiCoreInfo.hpp"
#include "modal/block/template_request.hpp"
#include "modal/block/template.hpp"
#include "currency_core/currency_format_utils.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class BlockTemplateController : public oatpp::web::server::api::ApiController {
private:
    OATPP_COMPONENT(std::shared_ptr<ApiCoreInfo>, m_core_info);
public:
    explicit BlockTemplateController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}
public:

    ENDPOINT_INFO(createBlockTemplate) {
        info->summary = "Create a block template for mining";
        info->addTag("Block");
        info->addConsumes<Object<BlockTemplateRequestModel>>("application/json");
        info->addResponse<Object<BlockTemplateModel>>(Status::CODE_200, "application/json");
        info->addResponse(Status::CODE_400, "text/plain");
        info->addResponse(Status::CODE_500, "text/plain");
    }
    ENDPOINT("POST", "/block/template", createBlockTemplate, BODY_DTO(Object<BlockTemplateRequestModel>, requestModel)) {
        currency::create_block_template_params params = AUTO_VAL_INIT(params);

        if (!currency::get_account_address_from_str(params.miner_address, *requestModel->miner_address)) {
            return createResponse(Status::CODE_400, "Failed to parse miner_address");
        }
        if (requestModel->stakeholder_address && !currency::get_account_address_from_str(params.stakeholder_address, *requestModel->stakeholder_address)) {
            return createResponse(Status::CODE_400, "Failed to parse stakeholder_address");
        }

        params.ex_nonce = requestModel->ex_nonce ? *requestModel->ex_nonce : "";
        params.pos = requestModel->pos;
        params.ignore_pow_ts_check = requestModel->ignore_pow_ts_check;

        if (requestModel->pe) {
            params.pe.amount = requestModel->pe->amount;
            params.pe.g_index = requestModel->pe->g_index;
            epee::string_tools::hex_to_pod(*requestModel->pe->keyimage, params.pe.keyimage);
            params.pe.block_timestamp = requestModel->pe->block_timestamp;
            params.pe.stake_unlock_time = requestModel->pe->stake_unlock_time;
            epee::string_tools::hex_to_pod(*requestModel->pe->tx_id, params.pe.tx_id);
            params.pe.tx_out_index = requestModel->pe->tx_out_index;
            params.pe.wallet_index = requestModel->pe->wallet_index;
        }

        for (const auto& tx_hex : *requestModel->explicit_txs) {
            currency::transaction tx;
            currency::blobdata tx_blob;
            if (!epee::string_tools::parse_hexstr_to_binbuff(*tx_hex, tx_blob) || !currency::parse_and_validate_tx_from_blob(tx_blob, tx)) {
                return createResponse(Status::CODE_400, "Failed to parse explicit_txs");
            }
            params.explicit_txs.push_back(tx);
        }

        currency::create_block_template_response response = AUTO_VAL_INIT(response);
        if (!m_core_info->getCore().get_block_template(params, response)) {
            return createResponse(Status::CODE_500, "Internal error: failed to create block template");
        }

        auto model = BlockTemplateModel::createShared();
        model->blocktemplate_blob = epee::string_tools::buff_to_hex_nodelimer(t_serializable_object_to_blob(response.b));
        model->difficulty = response.diffic.convert_to<std::string>();
        model->height = response.height;
        model->block_reward_without_fee = response.block_reward_without_fee;
        model->block_reward = response.block_reward;
        model->txs_fee = response.txs_fee;
        model->prev_hash = epee::string_tools::pod_to_hex(response.b.prev_id);
        model->seed = epee::string_tools::pod_to_hex(currency::ethash_epoch_to_seed(currency::ethash_height_to_epoch(response.height)));

        auto tgc_model = TxGenerationContextModel::createShared();
        // This is a very complex object with many cryptographic details.
        // For now, we will leave it empty as it's not essential for basic mining.
        // A dedicated endpoint could be created later to expose this if needed.
        model->miner_tx_tgc = tgc_model;

        return createDtoResponse(Status::CODE_200, model);
    }
};

#include OATPP_CODEGEN_END(ApiController)

#endif /* BlockTemplateController_hpp */
