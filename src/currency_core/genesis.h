// Copyright (c) 2014-2025 Zano Project
// Copyright (c) 2014-2018 The Louisdor Project
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#pragma once
#include <string>
#include <cstdint>

namespace currency
{
#pragma pack(push, 1)
#ifndef TESTNET
#include "_genesis.h.gen"
#else
#include "_genesis_tn.h.gen"
#endif
#pragma pack(pop)
  extern const genesis_tx_raw_data ggenesis_tx_raw;
}
