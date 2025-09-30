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
#include <type_traits> 
#include <boost/serialization/optional.hpp>

// boost::optional
template <template <bool> class Archive, class T>
bool do_serialize(Archive<false> &ar, boost::optional<T> &o)
{
  //reading flag
  bool is_none = false;
  if (!::do_serialize(ar, is_none))
  {
    ar.stream().setstate(std::ios::failbit);
    return false;
  }
  if (is_none)
  {
    o.reset();
    return true;
  }
  o = T();
  T& rval = o.value();
  //reading value
  if (!::do_serialize(ar, rval))
  {
    ar.stream().setstate(std::ios::failbit);
    return false;
  }

  return true;
}

template <template <bool> class Archive, class T>
bool do_serialize(Archive<true> &ar, boost::optional<T> &v)
{
  //writing flag
  bool is_none = !v.has_value();
  
  //make sure we don't put bool into json-like archives
  if constexpr (std::is_same_v<typename Archive<true>::variant_tag_type, const char*>) {
    if (is_none)
    {
      ar.begin_string();
      ar.end_string();
      return true;
    }
  }
  else {
    
    if (!::do_serialize(ar, is_none))
    {
      ar.stream().setstate(std::ios::failbit);
      return false;
    }
  }

  
  if (is_none)
  {
    return true;
  }

  if (!::do_serialize(ar, v.value()))
  {
    ar.stream().setstate(std::ios::failbit);
    return false;
  }

  return true;
}

// std::optional
template <template <bool> class Archive, class T>
bool do_serialize(Archive<false> &ar, std::optional<T> &o)
{
  //reading flag
  bool is_none = false;
  if (!::do_serialize(ar, is_none))
  {
    ar.stream().setstate(std::ios::failbit);
    return false;
  }
  if (is_none)
  {
    o.reset();
    return true;
  }
  o = T();
  T& rval = o.value();
  //reading value
  if (!::do_serialize(ar, rval))
  {
    ar.stream().setstate(std::ios::failbit);
    return false;
  }

  return true;
}

template <template <bool> class Archive, class T>
bool do_serialize(Archive<true> &ar, std::optional<T> &v)
{
  //writing flag
  bool is_none = !v.has_value();

  //make sure we don't put bool into json-like archives
  if constexpr (std::is_same_v<typename Archive<true>::variant_tag_type, const char*>) {
    if (is_none)
    {
      ar.begin_string();
      ar.end_string();
      return true;
    }
  }
  else {

    if (!::do_serialize(ar, is_none))
    {
      ar.stream().setstate(std::ios::failbit);
      return false;
    }
  }

  if (is_none)
  {
    return true;
  }

  if (!::do_serialize(ar, v.value()))
  {
    ar.stream().setstate(std::ios::failbit);
    return false;
  }

  return true;
}
