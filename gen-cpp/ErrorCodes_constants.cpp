/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "ErrorCodes_constants.h"

namespace impala {

const ErrorCodesConstants g_ErrorCodes_constants;

ErrorCodesConstants::ErrorCodesConstants() {
  TErrorMessage.push_back("");
  TErrorMessage.push_back("<UNUSED>");
  TErrorMessage.push_back("$0");
  TErrorMessage.push_back("$0");
  TErrorMessage.push_back("$0");
  TErrorMessage.push_back("$0");
  TErrorMessage.push_back("$0");
  TErrorMessage.push_back("$0");
  TErrorMessage.push_back("$0");
  TErrorMessage.push_back("$0");
  TErrorMessage.push_back("Parquet files should not be split into multiple hdfs-blocks. file=$0");
  TErrorMessage.push_back("Column metadata states there are $0 values, but read $1 values from column $2. file=$3");
  TErrorMessage.push_back("(unused)");
  TErrorMessage.push_back("ParquetScanner: reached EOF while deserializing data page header. file=$0");
  TErrorMessage.push_back("Metadata states that in group $0($1) there are $2 rows, but $3 rows were read.");
  TErrorMessage.push_back("(unused)");
  TErrorMessage.push_back("File '$0' column '$1' does not have the decimal precision set.");
  TErrorMessage.push_back("File '$0' column '$1' has a precision that does not match the table metadata  precision. File metadata precision: $2, table metadata precision: $3.");
  TErrorMessage.push_back("File '$0' column '$1' does not have converted type set to DECIMAL");
  TErrorMessage.push_back("File '$0' column '$1' contains decimal data but the table metadata has type $2");
  TErrorMessage.push_back("Problem parsing file $0 at $1$2");
  TErrorMessage.push_back("Decompressor: block size is too big.  Data is likely corrupt. Size: $0");
  TErrorMessage.push_back("Decompressor: invalid compressed length.  Data is likely corrupt.");
  TErrorMessage.push_back("Snappy: GetUncompressedLength failed");
  TErrorMessage.push_back("SnappyBlock: RawUncompress failed");
  TErrorMessage.push_back("Snappy: Decompressed size is not correct.");
  TErrorMessage.push_back("Unknown disk id.  This will negatively affect performance. Check your hdfs settings to enable block location metadata.");
  TErrorMessage.push_back("Reserved resource size ($0) is larger than query mem limit ($1), and will be restricted to $1. Configure the reservation size by setting RM_INITIAL_MEM.");
  TErrorMessage.push_back("Cannot perform join at hash join node with id $0. The input data was partitioned the maximum number of $1 times. This could mean there is significant skew in the data or the memory limit is set too low.");
  TErrorMessage.push_back("Cannot perform aggregation at hash aggregation node with id $0. The input data was partitioned the maximum number of $1 times. This could mean there is significant skew in the data or the memory limit is set too low.");
  TErrorMessage.push_back("Builtin '$0' with symbol '$1' does not exist. Verify that all your impalads are the same version.");
  TErrorMessage.push_back("RPC Error: $0");
  TErrorMessage.push_back("RPC timed out");
  TErrorMessage.push_back("Failed to verify function $0 from LLVM module $1, see log for more details.");
  TErrorMessage.push_back("File $0 corrupt. RLE level data bytes = $1");
  TErrorMessage.push_back("Column '$0' has conflicting Avro decimal types. Table schema $1: $2, file schema $1: $3");
  TErrorMessage.push_back("Column '$0' has conflicting Avro decimal types. Declared $1: $2, $1 in table's Avro schema: $3");
  TErrorMessage.push_back("Unresolvable types for column '$0': table type: $1, file type: $2");
  TErrorMessage.push_back("Unresolvable types for column '$0': declared column type: $1, table's Avro schema type: $2");
  TErrorMessage.push_back("Field $0 is missing from file and default values of type $1 are not yet supported.");
  TErrorMessage.push_back("Inconsistent table metadata. Mismatch between column definition and Avro schema: cannot read field $0 because there are only $1 fields.");
  TErrorMessage.push_back("Field $0 is missing from file and does not have a default value.");
  TErrorMessage.push_back("Field $0 is nullable in the file schema but not the table schema.");
  TErrorMessage.push_back("Inconsistent table metadata. Field $0 is not a record in the Avro schema.");
  TErrorMessage.push_back("Could not read definition level, even though metadata states there are $0 values remaining in data page. file=$1");
  TErrorMessage.push_back("Mismatched number of values in column index $0 ($1 vs. $2). file=$3");
  TErrorMessage.push_back("Failed to decode dictionary-encoded value. file=$0");
  TErrorMessage.push_back("SSL private-key password command ('$0') failed with error: $1");
  TErrorMessage.push_back("The SSL certificate path is blank");
  TErrorMessage.push_back("The SSL private key path is blank");
  TErrorMessage.push_back("The SSL certificate file does not exist at path $0");
  TErrorMessage.push_back("The SSL private key file does not exist at path $0");
  TErrorMessage.push_back("SSL socket creation failed: $0");
  TErrorMessage.push_back("Memory allocation of $0 bytes failed");
  TErrorMessage.push_back("Could not read repetition level, even though metadata states there are $0 values remaining in data page. file=$1");
  TErrorMessage.push_back("File '$0' has an incompatible Parquet schema for column '$1'. Column type: $2, Parquet schema:\n$3");
  TErrorMessage.push_back("Failed to allocate buffer for collection '$0'.");
  TErrorMessage.push_back("Temporary device for directory $0 is blacklisted from a previous error and cannot be used.");
  TErrorMessage.push_back("Temporary file $0 is blacklisted from a previous error and cannot be expanded.");
  TErrorMessage.push_back("RPC client failed to connect: $0");
  TErrorMessage.push_back("Metadata for file '$0' appears stale. Try running \"refresh $1\" to reload the file metadata.");
  TErrorMessage.push_back("File '$0' has an invalid version number: $1\nThis could be due to stale metadata. Try running \"refresh $2\".");
  TErrorMessage.push_back("Tried to read $0 bytes but could only read $1 bytes. This may indicate data file corruption. (file $2, byte offset: $3)");
  TErrorMessage.push_back("Invalid read of $0 bytes. This may indicate data file corruption. (file $1, byte offset: $2)");
  TErrorMessage.push_back("File '$0' has an invalid version header: $1\nMake sure the file is an Avro data file.");
  TErrorMessage.push_back("$0's allocations exceeded memory limits.");
  TErrorMessage.push_back("Cannot process row that is bigger than the IO size (row_size=$0, null_indicators_size=$1). To run this query, increase the IO size (--read_size option).");
  TErrorMessage.push_back("For better performance, snappy-, gzip-, and bzip-compressed files should not be split into multiple HDFS blocks. file=$0 offset $1");
  TErrorMessage.push_back("$0 Data error, likely data corrupted in this block.");
  TErrorMessage.push_back("$0 Decompressor error at $1, code=$2");
  TErrorMessage.push_back("Decompression failed to make progress, but end of input is not reached. File appears corrupted. file=$0");
  TErrorMessage.push_back("Unexpected end of compressed file. File may be truncated. file=$0");

}

} // namespace
