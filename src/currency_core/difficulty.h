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

#include <cstdint>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

#include "crypto/hash.h"

namespace currency
{
      
    typedef boost::multiprecision::uint128_t wide_difficulty_type;

    bool check_hash(const crypto::hash &hash, wide_difficulty_type difficulty);
    wide_difficulty_type next_difficulty_1(std::vector<std::uint64_t>& timestamps, std::vector<wide_difficulty_type>& cumulative_difficulties, size_t target_seconds, const wide_difficulty_type& difficulty_starter);
    wide_difficulty_type next_difficulty_2(std::vector<std::uint64_t>& timestamps, std::vector<wide_difficulty_type>& cumulative_difficulties, size_t target_seconds, const wide_difficulty_type& difficulty_starter);
    uint64_t difficulty_to_boundary(wide_difficulty_type difficulty);
    void difficulty_to_boundary_long(wide_difficulty_type difficulty, crypto::hash& result);
}
