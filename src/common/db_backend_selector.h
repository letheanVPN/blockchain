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

#include <boost/program_options.hpp>
#include "misc_language.h"
#include "db_backend_base.h"

namespace tools
{
  namespace db
  {
    enum db_engine_type { db_none = 0, db_lmdb, db_mdbx };
    
    class db_backend_selector
    {
    public:
      db_backend_selector();

      static void init_options(boost::program_options::options_description& desc);
      bool init(const boost::program_options::variables_map& vm);

      std::string get_db_folder_path() const;
      std::string get_db_main_file_name() const;
      db_engine_type get_engine_type() const { return m_engine_type; }
      std::string get_engine_name() const;
      std::string get_config_folder() const { return m_config_folder; }
      std::string get_temp_config_folder() const;
      std::string get_temp_db_folder_path() const;
 
      std::string get_pool_db_folder_path() const;

      std::shared_ptr<tools::db::i_db_backend> create_backend();

      std::string get_db_folder_path_old_1() const;
      std::string get_db_folder_path_old_2() const;

    private:
      db_engine_type m_engine_type;
      std::string m_config_folder;
    };

  } // namespace db
} // namespace tools
