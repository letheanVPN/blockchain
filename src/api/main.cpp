#include "ApiServer.hpp"
#include "oatpp/core/base/Environment.hpp"
#include "common/util.h"

int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();

  ApiServer server;

  tools::signal_handler::install([&server] {
    server.stop();
  });

  server.start();
  server.wait();
  
  /* Destroy oatpp Environment */
  oatpp::base::Environment::destroy();
  
  return 0;
}
