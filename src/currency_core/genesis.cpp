// Copyright (c) 2014-2025 Zano Project
// Copyright (c) 2014-2018 The Louisdor Project
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include "genesis.h"

namespace currency
{
#ifndef TESTNET
#include "generated/_genesis.cpp.gen"
#else
#include "generated/_genesis_tn.cpp.gen"
#endif
}
