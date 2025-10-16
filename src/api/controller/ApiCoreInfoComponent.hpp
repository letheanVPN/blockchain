#ifndef ApiCoreInfoComponent_hpp
#define ApiCoreInfoComponent_hpp

#include "currency_core/currency_core.h"
#include "p2p/net_node.h"
#include "currency_protocol/currency_protocol_handler.h"
#include "rpc/core_rpc_server.h"

// Define the p2p server type to avoid verbose template syntax
typedef nodetool::node_server<currency::t_currency_protocol_handler<currency::core>> p2psrv_t;

// A simple holder for core blockchain components that can be injected into controllers.
class ApiCoreInfoComponent {
private:
  currency::core& m_core;
  p2psrv_t& m_p2p;
  currency::core_rpc_server& m_rpc_server;

public:
  ApiCoreInfoComponent(currency::core& core, p2psrv_t& p2p, currency::core_rpc_server& rpc_server)
    : m_core(core), m_p2p(p2p), m_rpc_server(rpc_server)
  {}

  currency::core& getCore() { return m_core; }
  p2psrv_t& getP2p() { return m_p2p; }
  currency::core_rpc_server& getRpcServer() { return m_rpc_server; }
};

#endif /* ApiCoreInfoComponent_hpp */
