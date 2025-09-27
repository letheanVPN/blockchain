// Copyright (c) 2014-2018 Zano Project
// Copyright (c) 2014-2018 The Louisdor Project
// Copyright (c) 2012-2013 The Boolberry developers
// Copyright (c) 2017-2025 Lethean (https://lt.hn)
//
// Licensed under the European Union Public Licence (EUPL) version 1.2.
// You may obtain a copy of the licence at:
//
//     https://joinup.ec.europa.eu/software/page/eupl/licence-eupl
//
// The EUPL is a copyleft licence that is compatible with the MIT/X11
// licence used by the original projects; the MIT terms are therefore
// considered “grandfathered” under the EUPL for this code.
//
// SPDX‑License‑Identifier: EUPL-1.2
//

#pragma once
#include "net/http_server_handlers_map2.h"
#include "view_iface.h"

namespace plain_wallet
{
  struct error
  {
    std::string code;
    std::string message;
    BEGIN_KV_SERIALIZE_MAP()
      KV_SERIALIZE(code)
      KV_SERIALIZE(message)
    END_KV_SERIALIZE_MAP()
  };
  

//   struct open_wallet_response
//   {
//     view::transfers_array recent_history;
//     view::wallet_info wi;
//     BEGIN_KV_SERIALIZE_MAP()
//       KV_SERIALIZE(recent_history)
//       KV_SERIALIZE(wi)
//     END_KV_SERIALIZE_MAP()
//   };

  struct sync_status_response
  {
    bool finished;
    uint64_t progress;
    BEGIN_KV_SERIALIZE_MAP()
      KV_SERIALIZE(finished)
      KV_SERIALIZE(progress)
    END_KV_SERIALIZE_MAP()
  };

  struct basic_status_response
  {
    std::string status;
    BEGIN_KV_SERIALIZE_MAP()
      KV_SERIALIZE(status)
    END_KV_SERIALIZE_MAP()
  };

  struct configure_object
  {
    bool postponed_run_wallet = false;
    BEGIN_KV_SERIALIZE_MAP()
      KV_SERIALIZE(postponed_run_wallet)
    END_KV_SERIALIZE_MAP()
  };
  struct configure_response
  {
    std::string status;
    BEGIN_KV_SERIALIZE_MAP()
      KV_SERIALIZE(status)
    END_KV_SERIALIZE_MAP()
  };

} // namespace tools
