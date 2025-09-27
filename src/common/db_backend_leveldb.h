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
#include "include_base_utils.h"

// #include "db_backend_base.h"
// 
// #include "currency_db_base.h"
// #include "leveldb/db.h"
// #include "common/boost_serialization_helper.h"
// #include "common/difficulty_boost_serialization.h"
// #include "currency_format_utils.h"
// 
// 
// namespace tools
// {
//   namespace db
//   {
//     typedef leveldb::DB* db_handle;
// 
//     static const db_handle err_handle = nullptr;
// 
//     class level_db_backend : public i_db_backend
//     {
//       std::string m_path;
//       db_handle m_pdb;
//     public:
//       level_db_backend() :m_pdb(nullptr)
//       {}
//       ~level_db_backend(){ close(); }
//       bool close();
//       void begin_transaction();
//       void commit_transaction();
//       bool open(const std::string& path);
//       bool erase(const char* k, size s);
//       bool get(const char* k, size s, std::string& res_buff);
//       bool clear();
//       bool set(const char* k, size s, const char* v, size vs);
//     };
//   }
// }


