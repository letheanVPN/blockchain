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

#ifndef ApiCoreInfo_hpp
#define ApiCoreInfo_hpp

#include "currency_core/currency_core.h"
#include "p2p/net_node.h"
#include "currency_protocol/currency_protocol_handler.h"
#include "rpc/core_rpc_server.h"

// Define the p2p server type to avoid verbose template syntax
typedef nodetool::node_server<currency::t_currency_protocol_handler<currency::core>> p2psrv_t;

// A simple holder for core blockchain components that can be injected into controllers.
class ApiCoreInfo {
private:
  currency::core& m_core;
  p2psrv_t& m_p2p;
  currency::core_rpc_server& m_rpc_server;

public:
  ApiCoreInfo(currency::core& core, p2psrv_t& p2p, currency::core_rpc_server& rpc_server)
    : m_core(core), m_p2p(p2p), m_rpc_server(rpc_server)
  {}

  currency::core& getCore() { return m_core; }
  p2psrv_t& getP2p() { return m_p2p; }
  currency::core_rpc_server& getRpcServer() { return m_rpc_server; }
};

#endif /* ApiCoreInfo_hpp */
