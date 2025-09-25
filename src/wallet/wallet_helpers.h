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


#include "wallet2.h"
#include "view_iface.h"


namespace tools
{
  inline bool get_wallet_info(wallet2& w, view::wallet_info& wi)
  {
    wi = AUTO_VAL_INIT_T(view::wallet_info);
    wi.address = w.get_account().get_public_address_str();
    wi.view_sec_key = epee::string_tools::pod_to_hex(w.get_account().get_keys().view_secret_key);
    w.balance(wi.balances, wi.mined_total);
    wi.path = epee::string_encoding::wstring_to_utf8(w.get_wallet_path());
    wi.is_auditable = w.is_auditable();
    wi.is_watch_only = w.is_watch_only();
    wi.has_bare_unspent_outputs = w.has_bare_unspent_outputs();
    return true;
  }

  inline std::string get_seed_phrase_info(const std::string& seed_phrase, const std::string& seed_password, view::seed_phrase_info& result)
  {
    //cut the last timestamp word from restore_dats
    try
    {
      //restore_from_tracking_seed
      bool is_tracking = currency::account_base::is_seed_tracking(seed_phrase);
      if (is_tracking)
      {
        currency::account_base acc;
        result.require_password = false;
        result.hash_sum_matched = false;
        result.syntax_correct = acc.restore_from_tracking_seed(seed_phrase);
        if (result.syntax_correct)
        {
          result.tracking = true;
          result.address = acc.get_public_address_str();
        }
      }
      else
      {
        result.syntax_correct = currency::account_base::is_seed_password_protected(seed_phrase, result.require_password);
        if (result.syntax_correct )
        {
          if (result.require_password)
          {
            if (seed_password.size())
            {
              currency::account_base acc;
              result.hash_sum_matched = acc.restore_from_seed_phrase(seed_phrase, seed_password);
              if (result.hash_sum_matched)
              {
                result.address = acc.get_public_address_str();
              }
            }
            else
            {
              result.hash_sum_matched = false;
            }
          }
          else
          {
            currency::account_base acc;
            result.syntax_correct = acc.restore_from_seed_phrase(seed_phrase, "");
            if (result.syntax_correct)
            {
              result.address = acc.get_public_address_str();
            }            
          }
        }
      }
      return API_RETURN_CODE_OK;
    }
    catch (...)
    {
      result.syntax_correct = false;
      return API_RETURN_CODE_OK;
    }
  }
}