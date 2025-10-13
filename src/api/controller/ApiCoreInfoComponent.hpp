#ifndef ApiCoreInfoComponent_hpp
#define ApiCoreInfoComponent_hpp

#include "currency_core/currency_core.h"
#include "currency_protocol/currency_protocol_handler.h" // Full definition needed for template instantiation
#include "p2p/net_node.h"

// A simple holder for core blockchain components that can be injected into controllers.
class ApiCoreInfoComponent {
private:
  currency::core& m_core;
  nodetool::node_server<currency::t_currency_protocol_handler<currency::core>>& m_p2p;

public:
  ApiCoreInfoComponent(currency::core& core, nodetool::node_server<currency::t_currency_protocol_handler<currency::core>>& p2p)
    : m_core(core), m_p2p(p2p)
  {}

  currency::core& getCore() { return m_core; }
  nodetool::node_server<currency::t_currency_protocol_handler<currency::core>>& getP2p() { return m_p2p; }
};

#endif /* ApiCoreInfoComponent_hpp */
