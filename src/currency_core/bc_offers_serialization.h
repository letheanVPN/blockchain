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

#include <boost/serialization/vector.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/variant.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/map.hpp>
#include <boost/foreach.hpp>
#include <boost/serialization/is_bitwise_serializable.hpp>
#include "common/unordered_containers_boost_serialization.h"
#include "common/crypto_serialization.h"
#include "offers_service_basics.h"
#include "offers_services_helpers.h"

namespace boost
{
  namespace serialization
  {
    template <class Archive>
    inline void serialize(Archive &a, bc_services::offer_details &x, const boost::serialization::version_type ver)
    {
      a & x.offer_type;
      a & x.amount_primary;
      a & x.amount_target;
      a & x.bonus;
      a & x.target;
      a & x.primary;
      a & x.location_country;
      a & x.location_city;
      a & x.contacts;
      a & x.comment;
      a & x.payment_types;
      a & x.expiration_time;
      a & x.category;
      a & x.deal_option;

    }


    template <class Archive>
    inline void serialize(Archive& a, bc_services::offer_details_ex& x, const boost::serialization::version_type ver)
    {
      a & static_cast<bc_services::offer_details&>(x);
      a & x.timestamp;
      a & x.tx_hash;
      a & x.index_in_tx;
      a & x.tx_original_hash;
      a & x.fee;
      a & x.stopped;
      a & x.security;
    }

    template <class Archive>
    inline void serialize(Archive& a, bc_services::offer_details_ex_with_hash& x, const boost::serialization::version_type ver)
    {
      a & static_cast<bc_services::offer_details_ex&>(x);
      a & x.h;
      a & x.nxt_offer;
    }

    template <class Archive>
    inline void serialize(Archive &a, bc_services::cancel_offer &x, const boost::serialization::version_type ver)
    {
      a & x.offer_index;
      a & x.sig;
      a & x.tx_id;
    }

    template <class Archive>
    inline void serialize(Archive &a, bc_services::update_offer &x, const boost::serialization::version_type ver)
    {
      a & x.of;
      a & x.offer_index;
      a & x.sig;
      a & x.tx_id;
    }
  }
}