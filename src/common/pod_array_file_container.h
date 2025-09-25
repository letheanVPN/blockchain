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
#include <boost/filesystem/fstream.hpp>
#include <boost/filesystem/operations.hpp>

namespace tools
{

  template<typename pod_t>
  class pod_array_file_container
  {
  public:
    pod_array_file_container()
    {}

    ~pod_array_file_container()
    {
      close();
    }

    bool open(const std::wstring& filename, bool create_if_not_exist, bool* p_corrupted = nullptr, std::string* p_reason = nullptr)
    {
      if (!create_if_not_exist && !boost::filesystem::exists(filename))
      {
        if (p_reason)
          *p_reason = "file doest not exist";
        return false;
      }

      m_stream.open(filename, std::ios::binary | std::ios::app | std::ios::in);
      if (m_stream.rdstate() != std::ios::goodbit && m_stream.rdstate() != std::ios::eofbit)
      {
        if (p_reason)
          *p_reason = "file could not be opened";
        return false;
      }

      if (p_corrupted)
        *p_corrupted = false;

      size_t file_size = size_bytes();
      if (file_size % sizeof(pod_t) != 0)
      {
        // currupted
        if (p_corrupted)
          *p_corrupted = true;

        size_t corrected_size = file_size - file_size % sizeof(pod_t);
        
        // truncate to nearest item boundary
        close();
        boost::filesystem::resize_file(filename, corrected_size);
        m_stream.open(filename, std::ios::binary | std::ios::app | std::ios::in);
        if ((m_stream.rdstate() != std::ios::goodbit && m_stream.rdstate() != std::ios::eofbit) ||
          size_bytes() != corrected_size)
        {
          if (p_reason)
            *p_reason = "truncation failed";
          return false;
        }

        if (p_reason)
          *p_reason = std::string("file was corrupted, truncated: ") + epee::string_tools::num_to_string_fast(file_size) + " -> " + epee::string_tools::num_to_string_fast(corrected_size);
      }

      m_filename = filename;
      return true;
    }

    void close()
    {
      m_stream.close();
    }

    bool push_back(const pod_t& item)
    {
      if (!is_opened_and_in_good_state())
        return false;

      m_stream.seekp(0, std::ios_base::end);
      m_stream.write(reinterpret_cast<const char*>(&item), sizeof item);
      
      if (m_stream.rdstate() != std::ios::goodbit && m_stream.rdstate() != std::ios::eofbit)
        return false;

      m_stream.flush();

      return true;
    }

    bool get_item(size_t index, pod_t& result) const
    {
      if (!is_opened_and_in_good_state())
        return false;

      size_t offset = index * sizeof result;
      m_stream.seekg(offset);
      if (m_stream.rdstate() != std::ios::goodbit)
        return false;

      m_stream.read(reinterpret_cast<char*>(&result), sizeof result);

      return m_stream.gcount() == sizeof result;
    }

    size_t size_bytes() const
    {
      if (!is_opened_and_in_good_state())
        return 0;

      m_stream.seekg(0, std::ios_base::end);
      return m_stream.tellg();
    }

    bool is_opened_and_in_good_state() const
    {
      if (!m_stream.is_open())
        return false;
      if (m_stream.rdstate() != std::ios::goodbit && m_stream.rdstate() != std::ios::eofbit)
        return false;
      return true;
    }

    size_t size() const
    {
      return size_bytes() / sizeof(pod_t);
    }

    bool clear()
    {
      if (!is_opened_and_in_good_state())
        return false;

      // close and re-open stream with trunc bit
      m_stream.close();
      m_stream.open(m_filename, std::ios::binary | std::ios::trunc | std::ios::in | std::ios::out);

      return is_opened_and_in_good_state();
    }

  private:
    mutable boost::filesystem::fstream m_stream;
    std::wstring m_filename;
  };

} // namespace tools
