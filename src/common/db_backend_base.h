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

#ifndef ENV32BIT
#define CACHE_SIZE uint64_t(uint64_t(1UL * 128UL) * 1024UL * 1024UL * 1024UL)
#else
#define CACHE_SIZE (1 * 1024UL * 1024UL * 1024UL)
#endif


namespace tools
{
  namespace db
  {
    typedef size_t container_handle;
    const uint64_t invalid_tx_id = 0;
    struct i_db_callback
    {
      virtual bool on_enum_item(uint64_t i, const void* pkey, uint64_t ks, const void* pval, uint64_t vs) = 0;
    };

    struct stat_info
    {
      uint64_t tx_count;
      uint64_t write_tx_count;
      uint64_t map_size;
    };

    struct i_db_backend
    {
      virtual bool close()=0;
      virtual bool begin_transaction(bool read_only = false) = 0;
      virtual bool commit_transaction()=0;
      virtual void abort_transaction()=0;
      virtual bool open(const std::string& path, uint64_t cache_sz = CACHE_SIZE) = 0;
      virtual bool open_container(const std::string& name, container_handle& h)=0;
      virtual bool close_container(container_handle& h) = 0;
      virtual bool erase(container_handle h, const char* k, size_t s) = 0;
      virtual uint64_t size(container_handle h) = 0;
      virtual bool get(container_handle h, const char* k, size_t s, std::string& res_buff) = 0;
      virtual bool set(container_handle h, const char* k, size_t s, const char* v, size_t vs) = 0;
      virtual bool clear(container_handle h) = 0;
      virtual bool enumerate(container_handle h, i_db_callback* pcb)=0;
      virtual bool get_stat_info(stat_info& si) = 0;
      virtual const char* name()=0;
      virtual ~i_db_backend(){};
    };
  }
}