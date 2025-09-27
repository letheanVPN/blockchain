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

#include <boost/multiprecision/cpp_int.hpp>

namespace boost
{
  namespace serialization
  {
    //---------------------------------------------------
    template <class archive_t>
    inline void serialize(archive_t &a, currency::wide_difficulty_type &x, const boost::serialization::version_type ver)
    {
      if(archive_t::is_loading::value)
      {
        //load high part
        uint64_t v = 0;        
#ifdef DEBUG_DIFFICULTY_SERIALIZATION
        std::cout << "loading" << ENDL;
#endif
        a & v; 
        x = v;
#ifdef DEBUG_DIFFICULTY_SERIALIZATION
        std::cout << "hight part: " << std::hex << v << ENDL;
#endif
        //load low part
        x = x << 64;
        a & v;
#ifdef DEBUG_DIFFICULTY_SERIALIZATION
        std::cout << "low part: " << std::hex << v << ENDL;
#endif
        x += v;
#ifdef DEBUG_DIFFICULTY_SERIALIZATION
        std::cout << "loaded value: " << std::hex << x << ENDL;
#endif
      }else
      {
#ifdef DEBUG_DIFFICULTY_SERIALIZATION
        std::cout << "storing" << ENDL;
#endif
        //store high part
        currency::wide_difficulty_type x_ = x;
#ifdef DEBUG_DIFFICULTY_SERIALIZATION
        std::cout << "original: " << std::hex << x_ << ENDL;
#endif
        x_ = x_ >> 64;
        uint64_t v = x_.convert_to<uint64_t>();
#ifdef DEBUG_DIFFICULTY_SERIALIZATION
        std::cout << "hight part: " << std::hex << v << ENDL;
#endif
        a & v;         
        //store low part
        x_ = x;
        x_ = x_ << 64;
        x_ = x_ >> 64;
        v = x_.convert_to<uint64_t>();
#ifdef DEBUG_DIFFICULTY_SERIALIZATION
        std::cout << "low part: " << std::hex << v << ENDL;
#endif
        a & v;
      }      
    }
  }
}
