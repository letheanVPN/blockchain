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

#ifndef BlockHeightController_hpp
#define BlockHeightController_hpp

#include "modal/block/height.hpp"
#include "controller/ApiCoreInfo.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

/**
 *  Block Height Controller
 */
class BlockHeightController : public oatpp::web::server::api::ApiController {
private:
  OATPP_COMPONENT(std::shared_ptr<ApiCoreInfo>, m_core_info);
public:
  explicit BlockHeightController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:

  ENDPOINT_INFO(getHeight) {
    info->summary = "Get the current blockchain height";
    info->addTag("Block");
    info->addResponse<Object<HeightModel>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/block/height", getHeight) {
    auto model = HeightModel::createShared();
    model->height = m_core_info->getCore().get_current_blockchain_size();
    return createDtoResponse(Status::CODE_200, model);
  }

};

#include OATPP_CODEGEN_END(ApiController)

#endif /* BlockHeightController_hpp */
