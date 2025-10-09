#ifndef InfoController_hpp
#define InfoController_hpp

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class InfoController : public oatpp::web::server::api::ApiController {
public:
  InfoController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:

  ENDPOINT_INFO(version) {
    info->summary = "Get API version";
    info->description = "Returns the current version of the API.";
  }
  ENDPOINT("GET", "/version", version) {
    return createResponse(Status::CODE_200, "v0.0.1");
  }

  ENDPOINT_INFO(root) {
    info->summary = "Get info root";
    info->description = "Returns a placeholder for the info root.";
  }
  ENDPOINT("GET", "/", root) {
    return createResponse(Status::CODE_200, "Info root");
  }

};

#include OATPP_CODEGEN_END(ApiController)

#endif /* InfoController_hpp */
