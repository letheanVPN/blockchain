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
#include "version.h"
#include "dto/VersionDto.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

/**
 *  Info Controller
 */
class InfoController : public oatpp::web::server::api::ApiController {
public:
  explicit InfoController(OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:

  ENDPOINT_INFO(version)
  {
    info->addTag("Info");
    info->summary     = "Get API version";
    info->description = "Returns the current version of the API.";
    info->addResponse<Object<VersionDto>>(Status::CODE_200, "application/json");
  }
  ENDPOINT("GET", "/info/version", version)
  {
    auto dto          = VersionDto::createShared();
    dto->version      = PROJECT_VERSION;
    dto->version_long = PROJECT_VERSION_LONG;
    dto->major        = PROJECT_MAJOR_VERSION;
    dto->minor        = PROJECT_MINOR_VERSION;
    dto->revision     = PROJECT_REVISION;
    return createDtoResponse(Status::CODE_200, dto);
  }

};

#include OATPP_CODEGEN_END(ApiController)

#endif /* InfoController_hpp */
