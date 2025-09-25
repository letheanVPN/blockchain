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
#include <boost/program_options/variables_map.hpp>
#include "dispatch_core_events.h"
#include "core_runtime_config.h"

namespace currency
{
  struct i_bc_service
  {
    virtual ~i_bc_service() = default;

    virtual std::string get_id() = 0;
    virtual bool init(const std::string& config_folder, const boost::program_options::variables_map& vm) = 0;
    virtual bool deinit() = 0;
    virtual void handle_entry_push(const tx_service_attachment& a, size_t i, const transaction& tx, uint64_t h, const crypto::hash& bl_id, uint64_t timestamp) = 0;
    virtual void handle_entry_pop(const tx_service_attachment& a, size_t i, const transaction& tx, uint64_t h, uint64_t timestamp) = 0;
    virtual bool validate_entry(const tx_service_attachment& a, size_t i, const transaction& tx) = 0;
    virtual void set_event_handler(i_core_event_handler* event_handler) = 0;
    virtual void set_core_runtime_config(const core_runtime_config& rtc) = 0;
  };

  class bc_attachment_services_manager
  {
  public:
    bc_attachment_services_manager(/* i_core_event_handler* pcore_event_handler*/) : /*m_pcore_event_handler(pcore_event_handler),*/ m_core_runtime_config(get_default_core_runtime_config())
    {}
  

    void set_event_handler(i_core_event_handler* event_handler);
    void set_core_runtime_config(const core_runtime_config& rtc);
    bool add_service(i_bc_service* psrv);
    i_bc_service* get_service_by_id(const std::string& id) const;
    bool init(const std::string& config_folder, const boost::program_options::variables_map& vm);
    bool deinit();
    bool validate_entry(const tx_service_attachment& a, size_t i, const transaction& tx);
    void handle_entry_push(const tx_service_attachment& a, size_t i, const transaction& tx, uint64_t h, const crypto::hash& bl_id, uint64_t timestamp);
    void handle_entry_pop(const tx_service_attachment& a, size_t i, const transaction& tx, uint64_t h, uint64_t timestamp);
  
  private:
    std::map<std::string, i_bc_service*> m_services;
    //i_core_event_handler* m_pcore_event_handler;
    core_runtime_config m_core_runtime_config;

  };

}
