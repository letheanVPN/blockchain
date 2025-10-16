// Copyright (c) 2017-2025 Lethean (https://lt.hn)
//
// Licensed under the European Union Public Licence (EUPL) version 1.2.
// You may obtain a copy of the licence at:
//
//     https://joinup.ec.europa.eu/software/page/eupl/licence-eupl
//
// The EUPL is a copyleft licence that is compatible with the MIT/X11
// licence used by the original projects; but maintains OSS status,
// where regional copyright law requires ownership to dictate licence terms.
//
// SPDX‑License‑Identifier: EUPL-1.2
//

#ifndef VersionDto_hpp
#define VersionDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class VersionDto final : public oatpp::DTO
{
  DTO_INIT(VersionDto, DTO);

  DTO_FIELD(String, version);
  DTO_FIELD(String, version_long);
  DTO_FIELD(String, major);
  DTO_FIELD(String, minor);
  DTO_FIELD(String, revision);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* VersionDto_hpp */
