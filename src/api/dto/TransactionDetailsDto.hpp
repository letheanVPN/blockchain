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

#ifndef TransactionDetailsDto_hpp
#define TransactionDetailsDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  DTO for transaction attachments.
 */
class TransactionAttachmentDto : public oatpp::DTO {
  DTO_INIT(TransactionAttachmentDto, DTO);
  DTO_FIELD(String, type, "type");
  DTO_FIELD(String, short_view, "short_view");
  DTO_FIELD(String, details_view, "details_view");
};

/**
 *  DTO for transaction extra data.
 */
class TransactionExtraDto : public oatpp::DTO {
  DTO_INIT(TransactionExtraDto, DTO);
  DTO_FIELD(String, type, "type");
  DTO_FIELD(String, short_view, "short_view");
  DTO_FIELD(String, details_view, "details_view");
};

/**
 *  DTO for transaction inputs.
 */
class TransactionInputDto : public oatpp::DTO {
  DTO_INIT(TransactionInputDto, DTO);
  DTO_FIELD(UInt64, amount, "amount");
  DTO_FIELD(Vector<UInt64>, global_indexes, "global_indexes");
  DTO_FIELD(String, htlc_origin, "htlc_origin");
  DTO_FIELD(String, kimage_or_ms_id, "kimage_or_ms_id");
  DTO_FIELD(UInt32, multisig_count, "multisig_count");
};

/**
 *  DTO for transaction outputs.
 */
class TransactionOutputDto : public oatpp::DTO {
  DTO_INIT(TransactionOutputDto, DTO);
  DTO_FIELD(UInt64, amount, "amount");
  DTO_FIELD(UInt64, global_index, "global_index");
  DTO_FIELD(Boolean, is_spent, "is_spent");
  DTO_FIELD(UInt32, minimum_sigs, "minimum_sigs");
  DTO_FIELD(Vector<String>, pub_keys, "pub_keys");
};

/**
 *  DTO for detailed transaction information.
 */
class TransactionDetailsDto : public oatpp::DTO {
  DTO_INIT(TransactionDetailsDto, DTO);
  DTO_FIELD(UInt64, amount, "amount");
  DTO_FIELD(List<Object<TransactionAttachmentDto>>, attachments, "attachments");
  DTO_FIELD(String, blob, "blob");
  DTO_FIELD(UInt64, blob_size, "blob_size");
  DTO_FIELD(List<Object<TransactionExtraDto>>, extra, "extra");
  DTO_FIELD(UInt64, fee, "fee");
  DTO_FIELD(String, id, "id");
  DTO_FIELD(List<Object<TransactionInputDto>>, ins, "ins");
  DTO_FIELD(Int64, keeper_block, "keeper_block");
  DTO_FIELD(String, object_in_json, "object_in_json");
  DTO_FIELD(List<Object<TransactionOutputDto>>, outs, "outs");
  DTO_FIELD(String, pub_key, "pub_key");
  DTO_FIELD(UInt64, timestamp, "timestamp");
};

#include OATPP_CODEGEN_END(DTO)

#endif /* TransactionDetailsDto_hpp */
