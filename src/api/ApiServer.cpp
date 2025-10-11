#include "ApiServer.hpp"
#include "controller/InfoController.hpp"
#include "controller/BlockController.hpp"

#include "oatpp/network/Server.hpp"
#include "oatpp-swagger/Controller.hpp"

#include <iostream>
#include "version.h"

void ApiServer::run() {

  /* Register Components in scope of run() method */
  Components components;

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  auto docEndpoints = std::make_shared<oatpp::web::server::api::Endpoints>();

  auto infoController = std::make_shared<InfoController>();
  docEndpoints->append(infoController->getEndpoints());

  auto blockController = std::make_shared<BlockController>();
  docEndpoints->append(blockController->getEndpoints());

  router->addController(infoController);
  router->addController(blockController);

  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)
  ([]
   {
     oatpp::swagger::DocumentInfo::Builder builder;

     builder
         .setTitle("Lethean Blockchain API")
         .setDescription("New API layer for Lethean")
         .setVersion(PROJECT_VERSION)
         .setContactName("Lethean")
         .setContactUrl("https://lt.hn/")
         .setLicenseName("EUPL-1.2")
         .setLicenseUrl("https://joinup.ec.europa.eu/software/page/eupl/licence-eupl")
         .addServer("http://localhost:8000", "server on localhost");

     return builder.build(); }());

  /* Create a Swagger-UI controller and add its endpoints to the router */
  auto swaggerController = oatpp::swagger::Controller::createShared(*docEndpoints);
  router->addController(swaggerController);

  /* Get a connection handler component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

  /* Get a connection provider component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

  /* Create a server which takes provided TCP connections and passes them to the HTTP connection handler */
  oatpp::network::Server server(connectionProvider, connectionHandler);

  /* Print server port */
  OATPP_LOGI("lethean-api", "Server running, API Docs: http://127.0.0.1:%s/swagger/ui",  static_cast<const char*>(connectionProvider->getProperty("port").getData()));

  /* Run server */
  server.run();
  
}
