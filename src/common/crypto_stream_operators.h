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
#include <string>
#include <sstream>
#include "include_base_utils.h"
#include "crypto/crypto.h"
#include "crypto/hash.h"
#include "crypto/RIPEMD160_helper.h"

bool parse_hash256(const std::string str_hash, crypto::hash& hash);

template <class T>
std::ostream &print_t(std::ostream &o, const T &v)
{
  return o << "" << epee::string_tools::pod_to_hex(v) << "";
}


template <class T>
std::ostream &print16(std::ostream &o, const T &v)
{
  return o << "" << epee::string_tools::pod_to_hex(v).substr(0, 5) << "..";
}

template <class T>
std::string print16(const T &v)
{
  return std::string("") + epee::string_tools::pod_to_hex(v).substr(0, 5) + "..";
}


namespace crypto
{
  inline std::ostream &operator <<(std::ostream &o, const crypto::public_key &v)      { return print_t(o, v); }
  inline std::ostream &operator <<(std::ostream &o, const crypto::secret_key &v)      { return print_t(o, v); }
  inline std::ostream &operator <<(std::ostream &o, const crypto::key_derivation &v)  { return print_t(o, v); }
  inline std::ostream &operator <<(std::ostream &o, const crypto::key_image &v)       { return print_t(o, v); }
  inline std::ostream &operator <<(std::ostream &o, const crypto::signature &v)       { return print_t(o, v); }
  inline std::ostream &operator <<(std::ostream &o, const crypto::hash &v)            { return print_t(o, v); }
  inline std::ostream &operator <<(std::ostream &o, const crypto::hash160 &v)         { return print_t(o, v); }
} // namespace crypto
