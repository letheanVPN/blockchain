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

#ifndef DbStatInfoModel_hpp
#define DbStatInfoModel_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class DbStatInfoModel final : public oatpp::DTO
{
  DTO_INIT(DbStatInfoModel, DTO);

  DTO_FIELD(UInt64, tx_count);
  DTO_FIELD(UInt64, write_tx_count);
  DTO_FIELD(UInt64, map_size);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* DbStatInfoModel_hpp */
