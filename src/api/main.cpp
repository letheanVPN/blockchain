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
