#include "ApiServer.hpp"
#include "oatpp/core/base/Environment.hpp"

int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();

  ApiServer server;
  server.run();
  
  /* Destroy oatpp Environment */
  oatpp::base::Environment::destroy();
  
  return 0;
}
