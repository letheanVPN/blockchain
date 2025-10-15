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

ENDPOINT_INFO(version)
{
  info->addTag("Info");
  info->summary     = "Get API version";
  info->description = "Returns the current version of the API.";
  info->addResponse<Object<VersionDto>>(Status::CODE_200, "application/json");
}
ENDPOINT("GET", "/info/version", version)
{
  auto dto          = VersionDto::createShared();
  dto->version      = PROJECT_VERSION;
  dto->version_long = PROJECT_VERSION_LONG;
  dto->major        = PROJECT_MAJOR_VERSION;
  dto->minor        = PROJECT_MINOR_VERSION;
  dto->revision     = PROJECT_REVISION;
  return createDtoResponse(Status::CODE_200, dto);
}
