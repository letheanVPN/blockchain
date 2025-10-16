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

#include "ApiServer.hpp"
#include "controller/ApiCoreInfo.hpp"
#include "controller/path/info.hpp"
#include "controller/path/block.hpp"
#include "controller/path/block/hash.hpp"
#include "controller/path/block/id.hpp"
#include "controller/path/info/version.hpp"

#include "oatpp/network/Server.hpp"
#include "oatpp-swagger/Controller.hpp"
#include "version.h"
#include "common/command_line.h"

namespace
{
  const command_line::arg_descriptor<uint16_t> arg_api_bind_port = {"api-bind-port", "Port for API server to bind to", 36943};
  const command_line::arg_descriptor<std::string> arg_api_bind_host = {"api-bind-host", "IP/Hostname for API server to bind to", "127.0.0.1"};
}

uint16_t ApiServer::m_port = 8000;
std::string ApiServer::m_host = "127.0.0.1";

void ApiServer::init_options(boost::program_options::options_description& desc) {
  command_line::add_arg(desc, arg_api_bind_port);
  command_line::add_arg(desc, arg_api_bind_host);
}

ApiServer::ApiServer(const boost::program_options::variables_map& vm, currency::core* ccore, p2psrv_t* p2p, currency::core_rpc_server* rpc_server)
  : m_vm(vm), m_ccore(ccore), m_p2p(p2p), m_rpc_server(rpc_server) {
  if (vm.count(arg_api_bind_port.name)) {
    m_port = vm[arg_api_bind_port.name].as<uint16_t>();
  }
  if (vm.count(arg_api_bind_host.name)) {
    m_host = vm[arg_api_bind_host.name].as<std::string>();
  }
}

void ApiServer::run() {

  /* Register Components in scope of run() method */
  Components components;

  OATPP_CREATE_COMPONENT(std::shared_ptr<ApiCoreInfo>, coreInfoComponent)
  ([this] {
    return std::make_shared<ApiCoreInfo>(*m_ccore, *m_p2p, *m_rpc_server);
  }());

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  auto docEndpoints = std::make_shared<oatpp::web::server::api::Endpoints>();

  /*
   * Create and register controllers, this list will get VERY large, but, it has to be this way as oatpp creates a
   * static routing file before compile time, can't dynamically add controllers, or, be smart AND also have project code awareness
   * by this list being large, it allows for per endpoint code separation;
   * any PR that tries to reduce this, MUST have unit tests to prove it works, no exceptions.
   */
  auto infoController = std::make_shared<InfoController>();
  docEndpoints->append(infoController->getEndpoints());
  router->addController(infoController);

  auto infoVersionController = std::make_shared<InfoVersionController>();
  docEndpoints->append(infoVersionController->getEndpoints());
  router->addController(infoVersionController);

  auto blockController = std::make_shared<BlockController>();
  docEndpoints->append(blockController->getEndpoints());
  router->addController(blockController);

  auto blockByHashController = std::make_shared<BlockByHashController>();
  docEndpoints->append(blockByHashController->getEndpoints());
  router->addController(blockByHashController);

  auto blockByIdController = std::make_shared<BlockByIdController>();
  docEndpoints->append(blockByIdController->getEndpoints());
  router->addController(blockByIdController);


  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)
  ([]
   {
     oatpp::swagger::DocumentInfo::Builder builder;

     builder
         .setTitle("Lethean Blockchain API")
         .setDescription("OpenAPI for Lethean Blockchain")
         .setVersion(PROJECT_VERSION)
         .setContactName("Lethean")
         .setContactUrl("https://lt.hn/")
         .setLicenseName("EUPL-1.2")
         .setLicenseUrl("https://joinup.ec.europa.eu/software/page/eupl/licence-eupl")
         .addServer("http://" + ApiServer::m_host + ":" + std::to_string(ApiServer::m_port), "Local Daemon")
         .addServer("http://seed.lethean.io:36943", "Seed Server");

     return builder.build(); }());

  /* Create a Swagger-UI controller and add its endpoints to the router */
  auto swaggerController = oatpp::swagger::Controller::createShared(*docEndpoints);
  router->addController(swaggerController);

  /* Get a connection handler component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

  /* Get a connection provider component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

  /* Create a server which takes provided TCP connections and passes them to the HTTP connection handler */
  m_server = std::make_shared<oatpp::network::Server>(connectionProvider, connectionHandler);

  /* Print server port */
  OATPP_LOGI("lethean-api", "Server running, API Docs: http://127.0.0.1:%s/swagger/ui",  static_cast<const char*>(connectionProvider->getProperty("port").getData()));

  /* Run server */
  m_server->run();
  
}

void ApiServer::start() {
  m_server_thread = std::thread(&ApiServer::run, this);
}

void ApiServer::stop() const
{
  if (m_server) {
    m_server->stop();
  }
}

void ApiServer::wait() {
  if (m_server_thread.joinable()) {
    m_server_thread.join();
  }
}
