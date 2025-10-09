#include "controller/RootController.hpp"
#include "ApiServer.hpp"

#include "oatpp/network/Server.hpp"
#include "oatpp-swagger/Controller.hpp"

#include <iostream>

void run() {
  /* Register Components in scope of run() method */
  ApiServer components;

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  /* Create RootController and add all of its endpoints to router */
  auto rootController = std::make_shared<RootController>();
  router->addController(rootController);

  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)([] {

  oatpp::swagger::DocumentInfo::Builder builder;

  builder
  .setTitle("Lethean Blockchain API")
  .setDescription("New API layer for Lethean")
  .setVersion("1.0")
  .setContactName("Lethean")
  .setContactUrl("https://lt.hn/")

  .setLicenseName("EUPL-1.2")
  .setLicenseUrl("https://joinup.ec.europa.eu/software/page/eupl/licence-eupl")

  .addServer("http://localhost:8000", "server on localhost");

  // When you are using the AUTHENTICATION() Endpoint-Macro you must add an SecurityScheme object (https://swagger.io/specification/#securitySchemeObject)
  // For basic-authentication you can use the default Basic-Authorization-Security-Scheme like this
  // For more complex authentication schemes you can use the oatpp::swagger::DocumentInfo::SecuritySchemeBuilder builder
  // Don't forget to add info->addSecurityRequirement("basic_auth") to your ENDPOINT_INFO() Macro!
  //.addSecurityScheme("basic_auth", oatpp::swagger::DocumentInfo::SecuritySchemeBuilder::DefaultBasicAuthorizationSecurityScheme());

  return builder.build();

}());

  /* Create Swagger-UI controller and add its endpoints to router */
  auto swaggerController = oatpp::swagger::Controller::createShared(rootController->getEndpoints());
  router->addController(swaggerController);

  /* Get connection handler component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

  /* Get connection provider component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

  /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
  oatpp::network::Server server(connectionProvider, connectionHandler);

  /* Print server port */
  OATPP_LOGI("lethean-api", "Server running on port %s", connectionProvider->getProperty("port").getData());

  /* Run server */
  server.run();
}

int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();

  run();

  /* Destroy oatpp Environment */
  oatpp::base::Environment::destroy();

  return 0;
}
