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

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/variables_map.hpp>

#undef LOG_DEFAULT_CHANNEL 
#define LOG_DEFAULT_CHANNEL "stratum"

namespace currency
{
  class core;
  struct stratum_server_impl;

  class stratum_server
  {
  public:
    static void init_options(boost::program_options::options_description& desc);
    static bool should_start(const boost::program_options::variables_map& vm);

    stratum_server(core* c);
    ~stratum_server();
    bool init(const boost::program_options::variables_map& vm);
    bool run(bool wait = true);
    bool deinit();
    bool timed_wait_server_stop(uint64_t ms);
    bool send_stop_signal();

  private:
    size_t m_threads_count;

    stratum_server_impl* m_impl;
    core* m_p_core;
  };
}

#undef LOG_DEFAULT_CHANNEL 
#define LOG_DEFAULT_CHANNEL NULL
