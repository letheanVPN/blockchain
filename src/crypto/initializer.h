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

#if defined(__GNUC__)
#define INITIALIZER(name) __attribute__((constructor(101))) static void name(void)
#define FINALIZER(name) __attribute__((destructor(101))) static void name(void)
#define REGISTER_FINALIZER(name) ((void) 0)

#elif defined(_MSC_VER)
#include <assert.h>
#include <stdlib.h>
// http://stackoverflow.com/questions/1113409/attribute-constructor-equivalent-in-vc
// http://msdn.microsoft.com/en-us/library/bb918180.aspx
#pragma section(".CRT$XCT", read)
#define INITIALIZER(name) \
  static void __cdecl name(void); \
  __declspec(allocate(".CRT$XCT")) void (__cdecl *const _##name)(void) = &name; \
  static void __cdecl name(void)
#define FINALIZER(name) \
  static void __cdecl name(void)
#define REGISTER_FINALIZER(name) \
  do { \
    int _res = atexit(name); \
    assert(_res == 0); \
  } while (0);

#else
#error Unsupported compiler
#endif
