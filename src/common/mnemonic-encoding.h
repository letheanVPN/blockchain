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

/*
 * This file and its cpp file are for translating Electrum-style word lists
 * into their equivalent byte representations for cross-compatibility with
 * that method of "backing up" one's wallet keys.
 */


#include <string>
#include <vector>

namespace tools
{
	namespace mnemonic_encoding
	{  
		constexpr int NUMWORDS = 1626;

		std::vector<unsigned char> text2binary(const std::string& text);
		std::string binary2text(const std::vector<unsigned char>& binary);
    std::string word_by_num(uint32_t n);
    uint64_t num_by_word(const std::string& w);
    bool valid_word(const std::string& w);
		const std::map<std::string, uint32_t>& get_words_map();
	}
}
