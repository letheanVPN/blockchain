#ifndef RootController_hpp
#define RootController_hpp

#include "./info/InfoController.hpp"
#include "../dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

class RootController : public oatpp::web::server::api::ApiController {
private:
  std::shared_ptr<InfoController> m_infoController;
public:
  RootController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper),
      m_infoController(std::make_shared<InfoController>(objectMapper))
  {}
public:

  // oatpp::web::server::api::Endpoints(m_infoController, "/info");

  ENDPOINT("GET", "/hello", root) {
    auto dto = MyDto::createShared();
    dto->message = "Hello World!";
    return createDtoResponse(Status::CODE_200, dto);
  }

};

#include OATPP_CODEGEN_END(ApiController)

#endif /* RootController_hpp */
