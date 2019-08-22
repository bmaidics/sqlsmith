/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "ErrorCodes_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace impala {

int _kTErrorCodeValues[] = {
  TErrorCode::OK,
  TErrorCode::UNUSED,
  TErrorCode::GENERAL,
  TErrorCode::CANCELLED,
  TErrorCode::ANALYSIS_ERROR,
  TErrorCode::NOT_IMPLEMENTED_ERROR,
  TErrorCode::RUNTIME_ERROR,
  TErrorCode::MEM_LIMIT_EXCEEDED,
  TErrorCode::INTERNAL_ERROR,
  TErrorCode::RECOVERABLE_ERROR,
  TErrorCode::PARQUET_MULTIPLE_BLOCKS,
  TErrorCode::PARQUET_COLUMN_METADATA_INVALID,
  TErrorCode::PARQUET_HEADER_PAGE_SIZE_EXCEEDED,
  TErrorCode::PARQUET_HEADER_EOF,
  TErrorCode::PARQUET_GROUP_ROW_COUNT_ERROR,
  TErrorCode::PARQUET_GROUP_ROW_COUNT_OVERFLOW,
  TErrorCode::PARQUET_MISSING_PRECISION,
  TErrorCode::PARQUET_WRONG_PRECISION,
  TErrorCode::PARQUET_BAD_CONVERTED_TYPE,
  TErrorCode::PARQUET_INCOMPATIBLE_DECIMAL,
  TErrorCode::SEQUENCE_SCANNER_PARSE_ERROR,
  TErrorCode::SNAPPY_DECOMPRESS_INVALID_BLOCK_SIZE,
  TErrorCode::SNAPPY_DECOMPRESS_INVALID_COMPRESSED_LENGTH,
  TErrorCode::SNAPPY_DECOMPRESS_UNCOMPRESSED_LENGTH_FAILED,
  TErrorCode::SNAPPY_DECOMPRESS_RAW_UNCOMPRESS_FAILED,
  TErrorCode::SNAPPY_DECOMPRESS_DECOMPRESS_SIZE_INCORRECT,
  TErrorCode::HDFS_SCAN_NODE_UNKNOWN_DISK,
  TErrorCode::FRAGMENT_EXECUTOR,
  TErrorCode::PARTITIONED_HASH_JOIN_MAX_PARTITION_DEPTH,
  TErrorCode::PARTITIONED_AGG_MAX_PARTITION_DEPTH,
  TErrorCode::MISSING_BUILTIN,
  TErrorCode::RPC_GENERAL_ERROR,
  TErrorCode::RPC_TIMEOUT,
  TErrorCode::UDF_VERIFY_FAILED,
  TErrorCode::PARQUET_CORRUPT_VALUE,
  TErrorCode::AVRO_DECIMAL_RESOLUTION_ERROR,
  TErrorCode::AVRO_DECIMAL_METADATA_MISMATCH,
  TErrorCode::AVRO_SCHEMA_RESOLUTION_ERROR,
  TErrorCode::AVRO_SCHEMA_METADATA_MISMATCH,
  TErrorCode::AVRO_UNSUPPORTED_DEFAULT_VALUE,
  TErrorCode::AVRO_MISSING_FIELD,
  TErrorCode::AVRO_MISSING_DEFAULT,
  TErrorCode::AVRO_NULLABILITY_MISMATCH,
  TErrorCode::AVRO_NOT_A_RECORD,
  TErrorCode::PARQUET_DEF_LEVEL_ERROR,
  TErrorCode::PARQUET_NUM_COL_VALS_ERROR,
  TErrorCode::PARQUET_DICT_DECODE_FAILURE,
  TErrorCode::SSL_PASSWORD_CMD_FAILED,
  TErrorCode::SSL_CERTIFICATE_PATH_BLANK,
  TErrorCode::SSL_PRIVATE_KEY_PATH_BLANK,
  TErrorCode::SSL_CERTIFICATE_NOT_FOUND,
  TErrorCode::SSL_PRIVATE_KEY_NOT_FOUND,
  TErrorCode::SSL_SOCKET_CREATION_FAILED,
  TErrorCode::MEM_ALLOC_FAILED,
  TErrorCode::PARQUET_REP_LEVEL_ERROR,
  TErrorCode::PARQUET_UNRECOGNIZED_SCHEMA,
  TErrorCode::COLLECTION_ALLOC_FAILED,
  TErrorCode::TMP_DEVICE_BLACKLISTED,
  TErrorCode::TMP_FILE_BLACKLISTED,
  TErrorCode::RPC_CLIENT_CONNECT_FAILURE,
  TErrorCode::STALE_METADATA_FILE_TOO_SHORT,
  TErrorCode::PARQUET_BAD_VERSION_NUMBER,
  TErrorCode::SCANNER_INCOMPLETE_READ,
  TErrorCode::SCANNER_INVALID_READ,
  TErrorCode::AVRO_BAD_VERSION_HEADER,
  TErrorCode::UDF_MEM_LIMIT_EXCEEDED,
  TErrorCode::BTS_BLOCK_OVERFLOW,
  TErrorCode::COMPRESSED_FILE_MULTIPLE_BLOCKS,
  TErrorCode::COMPRESSED_FILE_BLOCK_CORRUPTED,
  TErrorCode::COMPRESSED_FILE_DECOMPRESSOR_ERROR,
  TErrorCode::COMPRESSED_FILE_DECOMPRESSOR_NO_PROGRESS,
  TErrorCode::COMPRESSED_FILE_TRUNCATED
};
const char* _kTErrorCodeNames[] = {
  "OK",
  "UNUSED",
  "GENERAL",
  "CANCELLED",
  "ANALYSIS_ERROR",
  "NOT_IMPLEMENTED_ERROR",
  "RUNTIME_ERROR",
  "MEM_LIMIT_EXCEEDED",
  "INTERNAL_ERROR",
  "RECOVERABLE_ERROR",
  "PARQUET_MULTIPLE_BLOCKS",
  "PARQUET_COLUMN_METADATA_INVALID",
  "PARQUET_HEADER_PAGE_SIZE_EXCEEDED",
  "PARQUET_HEADER_EOF",
  "PARQUET_GROUP_ROW_COUNT_ERROR",
  "PARQUET_GROUP_ROW_COUNT_OVERFLOW",
  "PARQUET_MISSING_PRECISION",
  "PARQUET_WRONG_PRECISION",
  "PARQUET_BAD_CONVERTED_TYPE",
  "PARQUET_INCOMPATIBLE_DECIMAL",
  "SEQUENCE_SCANNER_PARSE_ERROR",
  "SNAPPY_DECOMPRESS_INVALID_BLOCK_SIZE",
  "SNAPPY_DECOMPRESS_INVALID_COMPRESSED_LENGTH",
  "SNAPPY_DECOMPRESS_UNCOMPRESSED_LENGTH_FAILED",
  "SNAPPY_DECOMPRESS_RAW_UNCOMPRESS_FAILED",
  "SNAPPY_DECOMPRESS_DECOMPRESS_SIZE_INCORRECT",
  "HDFS_SCAN_NODE_UNKNOWN_DISK",
  "FRAGMENT_EXECUTOR",
  "PARTITIONED_HASH_JOIN_MAX_PARTITION_DEPTH",
  "PARTITIONED_AGG_MAX_PARTITION_DEPTH",
  "MISSING_BUILTIN",
  "RPC_GENERAL_ERROR",
  "RPC_TIMEOUT",
  "UDF_VERIFY_FAILED",
  "PARQUET_CORRUPT_VALUE",
  "AVRO_DECIMAL_RESOLUTION_ERROR",
  "AVRO_DECIMAL_METADATA_MISMATCH",
  "AVRO_SCHEMA_RESOLUTION_ERROR",
  "AVRO_SCHEMA_METADATA_MISMATCH",
  "AVRO_UNSUPPORTED_DEFAULT_VALUE",
  "AVRO_MISSING_FIELD",
  "AVRO_MISSING_DEFAULT",
  "AVRO_NULLABILITY_MISMATCH",
  "AVRO_NOT_A_RECORD",
  "PARQUET_DEF_LEVEL_ERROR",
  "PARQUET_NUM_COL_VALS_ERROR",
  "PARQUET_DICT_DECODE_FAILURE",
  "SSL_PASSWORD_CMD_FAILED",
  "SSL_CERTIFICATE_PATH_BLANK",
  "SSL_PRIVATE_KEY_PATH_BLANK",
  "SSL_CERTIFICATE_NOT_FOUND",
  "SSL_PRIVATE_KEY_NOT_FOUND",
  "SSL_SOCKET_CREATION_FAILED",
  "MEM_ALLOC_FAILED",
  "PARQUET_REP_LEVEL_ERROR",
  "PARQUET_UNRECOGNIZED_SCHEMA",
  "COLLECTION_ALLOC_FAILED",
  "TMP_DEVICE_BLACKLISTED",
  "TMP_FILE_BLACKLISTED",
  "RPC_CLIENT_CONNECT_FAILURE",
  "STALE_METADATA_FILE_TOO_SHORT",
  "PARQUET_BAD_VERSION_NUMBER",
  "SCANNER_INCOMPLETE_READ",
  "SCANNER_INVALID_READ",
  "AVRO_BAD_VERSION_HEADER",
  "UDF_MEM_LIMIT_EXCEEDED",
  "BTS_BLOCK_OVERFLOW",
  "COMPRESSED_FILE_MULTIPLE_BLOCKS",
  "COMPRESSED_FILE_BLOCK_CORRUPTED",
  "COMPRESSED_FILE_DECOMPRESSOR_ERROR",
  "COMPRESSED_FILE_DECOMPRESSOR_NO_PROGRESS",
  "COMPRESSED_FILE_TRUNCATED"
};
const std::map<int, const char*> _TErrorCode_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(72, _kTErrorCodeValues, _kTErrorCodeNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));

} // namespace