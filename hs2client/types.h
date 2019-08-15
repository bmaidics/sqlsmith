// Copyright 2016 Cloudera Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef HS2CLIENT_TYPES_H
#define HS2CLIENT_TYPES_H

#include <memory>
#include "string"
namespace hs2client {

// Represents a column's type.
//
// For now only PrimitiveType is implemented, as thase are the only types Impala will
// currently return. In the future, nested types will be represented as other subclasses
// of ColumnType containing ptrs to other ColumnTypes - for example, an ArrayType subclass
// would contain a single ptr to another ColumnType representing the type of objects
// stored in the array.
class ColumnType {
 public:

  // Maps directly to TTypeId in the HiveServer2 interface.
  enum class TypeId {
    BOOLEAN,
    TINYINT,
    SMALLINT,
    INT,
    BIGINT,
    FLOAT,
    DOUBLE,
    STRING,
    TIMESTAMP,
    BINARY,
    ARRAY,
    MAP,
    STRUCT,
    UNION,
    USER_DEFINED,
    DECIMAL,
    NULL_TYPE,
    DATE,
    VARCHAR,
    CHAR,
    INVALID,
  };

  virtual const TypeId type_id() const = 0;
  virtual const std::string ToString() const = 0;
};

class PrimitiveType : public ColumnType {
 public:
  PrimitiveType(const TypeId& type_id) : type_id_(type_id) {}

  const TypeId type_id() const { return type_id_; }
  const std::string ToString() const;

 private:
  const TypeId type_id_;
};

// Represents CHAR and VARCHAR types.
class CharacterType : public PrimitiveType {
 public:
  CharacterType(const TypeId& type_id, int max_length)
    : PrimitiveType(type_id), max_length_(max_length) {}

  const int max_length() const { return max_length_; }

 private:
  const int max_length_;
};

// Represents DECIMAL types.
class DecimalType : public PrimitiveType {
 public:
  DecimalType(const TypeId& type_id, int precision, int scale)
    : PrimitiveType(type_id), precision_(precision), scale_(scale) {}

  const int precision() const { return precision_; }
  const int scale() const { return scale_; }

 private:
  const int precision_;
  const int scale_;
};

// Represents the metadata for a single column.
class ColumnDesc {
 public:
  ColumnDesc(const std::string& column_name, std::unique_ptr<ColumnType> type,
      int position, const std::string& comment)
    : column_name_(column_name), type_(move(type)), position_(position),
      comment_(comment) {}

  const std::string& column_name() const { return column_name_; }
  const ColumnType* type() const { return type_.get(); }
  const int position() const { return position_; }
  const std::string& comment() const { return comment_; }

  const PrimitiveType* GetPrimitiveType() const;
  const CharacterType* GetCharacterType() const;
  const DecimalType* GetDecimalType() const;

 private:
  const std::string column_name_;
  std::unique_ptr<ColumnType> type_;
  const int position_;
  const std::string comment_;
};

} // namespace hs2client

#endif // HS2CLIENT_TYPES_H
