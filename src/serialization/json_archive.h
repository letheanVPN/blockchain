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

/* json_archive.h
 *
 * JSON archive */

#pragma once

#include "serialization.h"
#include <cassert>
#include <iostream>
#include <iomanip>

template <class Stream, bool IsSaving>
struct json_archive_base
{
  typedef Stream stream_type;
  typedef json_archive_base<Stream, IsSaving> base_type;
  typedef boost::mpl::bool_<IsSaving> is_saving;

  typedef const char *variant_tag_type;

  json_archive_base(stream_type &s, bool indent = false) : stream_(s), indent_(indent), object_begin(false), depth_(0) { }

  void tag(const char *tag) {
    if (!object_begin)
      stream_ << ", ";
    make_indent();
    stream_ << '"' << tag << "\": ";
    object_begin = false;
  }

  void begin_object()
  {
    stream_ << "{";
    ++depth_;
    object_begin = true;
  }

  void end_object()
  {
    --depth_;
    make_indent();
    stream_ << "}";
  }

  void begin_variant() { begin_object(); }
  void end_variant() { end_object(); }
  Stream &stream() { return stream_; }

protected:
  void make_indent()
  {
    if (indent_)
    {
      stream_ << '\n' << std::string(2 * depth_, ' ');
    }
  }

protected:
  stream_type &stream_;
  bool indent_;
  bool object_begin;
  size_t depth_;
};

template <bool W>
struct json_archive;

template <>
struct json_archive<true> : public json_archive_base<std::ostream, true>
{
  json_archive(stream_type &s, bool indent = false) : base_type(s, indent), inner_array_size_{} { }

  template<typename T>
  static auto promote_to_printable_integer_type(T v) -> decltype(+v)
  {
    // Unary operator '+' performs integral promotion on type T [expr.unary.op].
    // If T is signed or unsigned char, it's promoted to int and printed as number.
    return +v;
  }
  bool is_saving_arch(){ return true; }

  template <class T>
  void serialize_int(T v)
  {
    stream_ << std::dec << promote_to_printable_integer_type(v);
  }

  template <class T>
  void serialize_uint(T v)
  {
    stream_ << std::dec << promote_to_printable_integer_type(v);
  }

  void serialize_blob(void *buf, size_t len, const char *delimiter="\"") {
    begin_string(delimiter);
    for (size_t i = 0; i < len; i++) {
      unsigned char c = ((unsigned char *)buf)[i];
      stream_ << std::hex << std::setw(2) << std::setfill('0') << (int)c;
    }
    end_string(delimiter);
  }

  template <class T>
  void serialize_varint(T &v)
  {
    stream_ << std::dec << promote_to_printable_integer_type(v);
  }

  void begin_string(const char *delimiter="\"")
  {
    stream_ << delimiter;
  }

  void end_string(const char *delimiter="\"")
  {
    stream_ << delimiter;
  }

  void begin_array(size_t s=0)
  {
    inner_array_size_ = s;
    ++depth_;
    stream_ << "[ ";
  }

  void delimit_array()
  {
    stream_ << ", ";
  }

  void end_array()
  {
    --depth_;
    if (0 < inner_array_size_)
    {
      make_indent();
    }
    stream_ << "]";
  }

  void write_variant_tag(const char *t)
  {
    tag(t);
  }

private:
  size_t inner_array_size_;
};

inline
bool do_serialize(json_archive<true>& ar, std::string& v)
{
    ar.begin_string();
    ar.stream() << epee::string_tools::buff_to_hex_nodelimer(v);
    ar.end_string();
    return true;
}

inline
bool do_serialize(json_archive<true>& ar, bool& v)
{
  if(v)
    ar.stream() << "true";
  else
    ar.stream() << "false";
  return true;
}

