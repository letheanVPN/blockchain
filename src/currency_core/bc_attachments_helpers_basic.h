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
#include "currency_basic.h"

namespace bc_services
{
  template<typename T>
  struct is_boost_variant : std::false_type {};

  template<typename... Args>
  struct is_boost_variant<boost::variant<Args...>> : std::true_type {};

  template<bool is_variant>
  struct type_selector;
  
  template<>
  struct type_selector<true>
  {
    template<typename t_type>
    static const std::type_info& get_type(const t_type& t)
    {
      return t.type();
    }
    template<typename t_type, typename t_return_type>
    static const t_return_type& get(const t_type& t)
    {
      return boost::get<t_return_type>(t);
    }
  };

  template<>
  struct type_selector<false>
  {
    template<typename t_type>
    static const std::type_info& get_type(const t_type& t)
    {
      return typeid(t);
    }
    template<typename t_type, typename t_return_type>
    static const t_return_type& get(const t_type& t)
    {
      return t;
    }
  };

  template<class t_attachment_type_container_t>
  bool get_first_service_attachment_by_id(const t_attachment_type_container_t& tx_items, const std::string& id, const std::string& instruction, currency::tx_service_attachment& res)
  {
    for (const auto& item : tx_items)
    {
      typedef type_selector<is_boost_variant<typename t_attachment_type_container_t::value_type>::value> TS;
      if (TS::get_type(item) == typeid(currency::tx_service_attachment))
      {
        const currency::tx_service_attachment& tsa = TS::template get<decltype(item), currency::tx_service_attachment>(item);
        if (tsa.service_id == id && tsa.instruction == instruction)
        {
          res = tsa;
          return true;
        }
      }
    }
    return false;
  }

}
