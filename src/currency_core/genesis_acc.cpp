// Copyright (c) 2014-2018 Zano Project
// Copyright (c) 2014-2018 Zano Project
// Copyright (c) 2014-2018 The Louisdor Project
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "genesis_acc.h"


namespace currency
{
#ifndef TESTNET
const std::string ggenesis_tx_pub_key_str = "ad5e9cb3206847eeff5866a4732cfc44b0514dcf4c3af29e48604cc0b793fe4f";
const crypto::public_key ggenesis_tx_pub_key = epee::string_tools::parse_tpod_from_hex_string<crypto::public_key>(ggenesis_tx_pub_key_str);
extern const genesis_tx_dictionary_entry ggenesis_dict[1];
const genesis_tx_dictionary_entry ggenesis_dict[1] = {
  {11898974375199696328ULL,0}
};
#else
  const std::string ggenesis_tx_pub_key_str    = "cc27108a5c2af3ba4893ccbd50fdd919187503bda7299b0dbbdbc8acd6028b36";
  const crypto::public_key ggenesis_tx_pub_key = epee::string_tools::parse_tpod_from_hex_string<crypto::public_key>(ggenesis_tx_pub_key_str);
  const genesis_tx_dictionary_entry ggenesis_dict[5] = {
    { 4413532107669521528ULL, 2 },
    { 4848259848862559835ULL, 4 },
    { 4891306118630423916ULL, 1 },
    { 6536034028979999929ULL, 0 },
    { 15528122346224653564ULL, 3 }
};
#endif



}



