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

namespace tools
{
  class password_container
  {
  public:
    static const size_t max_password_size = 1024;

    password_container();
    password_container(std::string&& password);
    password_container(password_container&& rhs);
    ~password_container();

    void clear();
    bool empty() const { return m_empty; }
    const std::string& password() const { return m_password; }
    const std::string& get_input() const { return m_password; } // TODO: refactor this
    void password(std::string&& val) { m_password = std::move(val); m_empty = false; }
    bool read_password();
    bool read_password(const std::string& prompt_text);
    bool read_input(const std::string& prompt_text, char char_to_replace_user_input = '\0');

  private:
    bool read_from_file();
    bool read_from_tty(char char_to_replace_user_input);

  private:
    bool m_empty;
    std::string m_password;
  };
}
