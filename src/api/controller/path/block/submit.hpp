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

#ifndef BlockSubmitController_hpp
#define BlockSubmitController_hpp

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "controller/ApiCoreInfo.hpp"
#include "modal/block/submit_request.hpp"
#include "modal/block/submit_response.hpp"
#include "currency_core/currency_format_utils.h"
#include "currency_core/verification_context.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

class BlockSubmitController : public oatpp::web::server::api::ApiController {
private:
    OATPP_COMPONENT(std::shared_ptr<ApiCoreInfo>, m_core_info);
public:
    explicit BlockSubmitController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper) {}
public:

    ENDPOINT_INFO(submitBlock) {
        info->summary = "Submit a new block to the network";
        info->addTag("Block");
        info->addConsumes<Object<SubmitBlockRequestModel>>("application/json");
        info->addResponse<Object<SubmitBlockResponseModel>>(Status::CODE_200, "application/json");
        info->addResponse(Status::CODE_400, "text/plain");
        info->addResponse(Status::CODE_406, "text/plain");
    }
    ENDPOINT("POST", "/block/submit", submitBlock, BODY_DTO(Object<SubmitBlockRequestModel>, requestModel)) {
        if (!requestModel->block_blob || requestModel->block_blob->empty()) {
            return createResponse(Status::CODE_400, "Missing block_blob");
        }

        currency::blobdata blockblob;
        if (!epee::string_tools::parse_hexstr_to_binbuff(*requestModel->block_blob, blockblob)) {
            return createResponse(Status::CODE_400, "Wrong block blob");
        }

        currency::block b = AUTO_VAL_INIT(b);
        if (!currency::parse_and_validate_block_from_blob(blockblob, b)) {
            return createResponse(Status::CODE_400, "Wrong block blob");
        }

        currency::block_verification_context bvc = AUTO_VAL_INIT(bvc);
        if (!m_core_info->getCore().handle_block_found(b, &bvc)) {
            if (bvc.m_added_to_altchain) {
                return createResponse(Status::CODE_406, "Block added as alternative");
            }
            return createResponse(Status::CODE_406, "Block not accepted");
        }

        auto responseModel = SubmitBlockResponseModel::createShared();
        responseModel->status = "OK";
        return createDtoResponse(Status::CODE_200, responseModel);
    }
};

#include OATPP_CODEGEN_END(ApiController)

#endif /* BlockSubmitController_hpp */
