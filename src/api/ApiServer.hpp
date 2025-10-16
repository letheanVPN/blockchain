#ifndef ApiServer_hpp
#define ApiServer_hpp

#include "currency_core/blockchain_storage.h"
#include "currency_core/currency_core.h"
#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp/network/Server.hpp"
#include <thread>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

class ApiServer {
private:
  std::thread m_server_thread;
  std::shared_ptr<oatpp::network::Server> m_server;
  boost::program_options::variables_map m_vm;
  
  void run();

public:
  static uint16_t m_port;
  static std::string m_host;

  static void init_options(po::options_description& desc);

  ApiServer(const boost::program_options::variables_map& vm);
  
  class Components  {
  public:
    
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
      return oatpp::network::tcp::server::ConnectionProvider::createShared({ApiServer::m_host, ApiServer::m_port, oatpp::network::Address::IP_4});
    }());
    
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
      return oatpp::web::server::HttpRouter::createShared();
    }());
    
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)([] {
      OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
      return oatpp::web::server::HttpConnectionHandler::createShared(router);
    }());
    
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
      auto jsonMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
      jsonMapper->getSerializer()->getConfig()->useBeautifier = true;
      return jsonMapper;
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)([] {
      return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
    }());

  };

  void start();
  void stop();
  void wait();

};

#endif /* ApiServer_hpp */
