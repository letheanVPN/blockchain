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

#include "p2p/net_node_common.h"
#include "currency_protocol/currency_protocol_defs.h"
#include "currency_core/connection_context.h"
namespace currency
{
  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  struct i_currency_protocol
  {
    virtual bool relay_block(NOTIFY_NEW_BLOCK::request& arg, currency_connection_context& exclude_context)=0;
    virtual bool relay_transactions(NOTIFY_OR_INVOKE_NEW_TRANSACTIONS::request& arg, currency_connection_context& exclude_context)=0;
    virtual void on_hardfork_activated(size_t hardfork_id) {}
    //virtual bool request_objects(NOTIFY_REQUEST_GET_OBJECTS::request& arg, currency_connection_context& context)=0;
  };

  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  struct currency_protocol_stub: public i_currency_protocol
  {
    virtual bool relay_block(NOTIFY_NEW_BLOCK::request& /*arg*/, currency_connection_context& /*exclude_context*/)
    {
      return false;
    }
    virtual bool relay_transactions(NOTIFY_OR_INVOKE_NEW_TRANSACTIONS::request& /*arg*/, currency_connection_context& /*exclude_context*/)
    {
      return false;
    }

  };

  /************************************************************************/
  /*                                                                      */
  /************************************************************************/
  struct i_critical_error_handler
  {
    // called by currency protocol when the time is critically out of sync
    // return true if the error is not ignored and the called should not proceed
    virtual bool on_critical_time_sync_error() = 0;
    
    virtual bool on_critical_low_free_space(uint64_t available, uint64_t required) = 0;

    virtual bool on_immediate_stop_requested() = 0;
  };


}
