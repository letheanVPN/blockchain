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

#include "bc_attachments_service_manager.h"

namespace currency
{
  bool bc_attachment_services_manager::add_service(i_bc_service* pservice)
  {
    if (pservice == nullptr)
      return false;

    if (m_services.count(pservice->get_id()))
    {
      LOG_ERROR("Service with id " << pservice->get_id() << "already registered");
      return false;
    }
    m_services[pservice->get_id()] = pservice;
    pservice->set_core_runtime_config(m_core_runtime_config);
    return true;
  }
  i_bc_service* bc_attachment_services_manager::get_service_by_id(const std::string& id) const
  {
    const auto& it = m_services.find(id);
    if (it == m_services.end())
      return nullptr;

    return it->second;
  }
  void bc_attachment_services_manager::set_event_handler(i_core_event_handler* event_handler)
  {
    for (auto& s : m_services)
    {
      s.second->set_event_handler(event_handler);
    }
  }
  void bc_attachment_services_manager::set_core_runtime_config(const core_runtime_config& rtc)
  {
    m_core_runtime_config = rtc;
    for (auto& s : m_services)
    {
      s.second->set_core_runtime_config(rtc);
    }
  }
  bool bc_attachment_services_manager::init(const std::string& config_folder, const boost::program_options::variables_map& vm)
  {
    //add service 
    for (auto& s : m_services)
    {
      s.second->init(config_folder, vm);
    }
    return true;
  }
  bool bc_attachment_services_manager::deinit()
  {
    //add service 
    for (auto& s : m_services)
    {
      s.second->deinit();
    }
    m_services.clear();
    return true;
  }
  bool bc_attachment_services_manager::validate_entry(const tx_service_attachment& a, size_t i, const transaction& tx)
  {
    auto it = m_services.find(a.service_id);
    if (it != m_services.end())
    {
      return it->second->validate_entry(a, i, tx);
    }
    return false;
  }
  void bc_attachment_services_manager::handle_entry_push(const tx_service_attachment& a, size_t i, const transaction& tx, uint64_t h, const crypto::hash& bl_id, uint64_t timestamp)
  {
    auto it = m_services.find(a.service_id);
    if (it != m_services.end())
    {
      it->second->handle_entry_push(a, i, tx, h, bl_id, timestamp);
    }
  }
  void bc_attachment_services_manager::handle_entry_pop(const tx_service_attachment& a, size_t i, const transaction& tx, uint64_t h, uint64_t timestamp)
  {
    auto it = m_services.find(a.service_id);
    if (it != m_services.end())
    {
      it->second->handle_entry_pop(a, i, tx, h, timestamp);
    }
  }
}
