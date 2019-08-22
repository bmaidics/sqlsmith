/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Types_TYPES_H
#define Types_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>


namespace impala {

struct TPrimitiveType {
  enum type {
    INVALID_TYPE = 0,
    NULL_TYPE = 1,
    BOOLEAN = 2,
    TINYINT = 3,
    SMALLINT = 4,
    INT = 5,
    BIGINT = 6,
    FLOAT = 7,
    DOUBLE = 8,
    DATE = 9,
    DATETIME = 10,
    TIMESTAMP = 11,
    STRING = 12,
    BINARY = 13,
    DECIMAL = 14,
    CHAR = 15,
    VARCHAR = 16
  };
};

extern const std::map<int, const char*> _TPrimitiveType_VALUES_TO_NAMES;

struct TTypeNodeType {
  enum type {
    SCALAR = 0,
    ARRAY = 1,
    MAP = 2,
    STRUCT = 3
  };
};

extern const std::map<int, const char*> _TTypeNodeType_VALUES_TO_NAMES;

struct TStmtType {
  enum type {
    QUERY = 0,
    DDL = 1,
    DML = 2,
    EXPLAIN = 3,
    LOAD = 4,
    SET = 5
  };
};

extern const std::map<int, const char*> _TStmtType_VALUES_TO_NAMES;

struct TExplainLevel {
  enum type {
    MINIMAL = 0,
    STANDARD = 1,
    EXTENDED = 2,
    VERBOSE = 3
  };
};

extern const std::map<int, const char*> _TExplainLevel_VALUES_TO_NAMES;

struct TRuntimeFilterMode {
  enum type {
    OFF = 0,
    LOCAL = 1,
    GLOBAL = 2
  };
};

extern const std::map<int, const char*> _TRuntimeFilterMode_VALUES_TO_NAMES;

struct TFunctionCategory {
  enum type {
    SCALAR = 0,
    AGGREGATE = 1,
    ANALYTIC = 2
  };
};

extern const std::map<int, const char*> _TFunctionCategory_VALUES_TO_NAMES;

struct TFunctionBinaryType {
  enum type {
    BUILTIN = 0,
    JAVA = 1,
    NATIVE = 2,
    IR = 3
  };
};

extern const std::map<int, const char*> _TFunctionBinaryType_VALUES_TO_NAMES;

typedef int64_t TTimestamp;

typedef int32_t TPlanNodeId;

typedef int32_t TTupleId;

typedef int32_t TSlotId;

typedef int32_t TTableId;

class TScalarType;

class TStructField;

class TTypeNode;

class TColumnType;

class TNetworkAddress;

class TUniqueId;

class TFunctionName;

class TScalarFunction;

class TAggregateFunction;

class TFunction;

typedef struct _TScalarType__isset {
  _TScalarType__isset() : len(false), precision(false), scale(false) {}
  bool len :1;
  bool precision :1;
  bool scale :1;
} _TScalarType__isset;

class TScalarType {
 public:

  TScalarType(const TScalarType&);
  TScalarType& operator=(const TScalarType&);
  TScalarType() : type((TPrimitiveType::type)0), len(0), precision(0), scale(0) {
  }

  virtual ~TScalarType() throw();
  TPrimitiveType::type type;
  int32_t len;
  int32_t precision;
  int32_t scale;

  _TScalarType__isset __isset;

  void __set_type(const TPrimitiveType::type val);

  void __set_len(const int32_t val);

  void __set_precision(const int32_t val);

  void __set_scale(const int32_t val);

  bool operator == (const TScalarType & rhs) const
  {
    if (!(type == rhs.type))
      return false;
    if (__isset.len != rhs.__isset.len)
      return false;
    else if (__isset.len && !(len == rhs.len))
      return false;
    if (__isset.precision != rhs.__isset.precision)
      return false;
    else if (__isset.precision && !(precision == rhs.precision))
      return false;
    if (__isset.scale != rhs.__isset.scale)
      return false;
    else if (__isset.scale && !(scale == rhs.scale))
      return false;
    return true;
  }
  bool operator != (const TScalarType &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TScalarType & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TScalarType &a, TScalarType &b);

inline std::ostream& operator<<(std::ostream& out, const TScalarType& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _TStructField__isset {
  _TStructField__isset() : comment(false) {}
  bool comment :1;
} _TStructField__isset;

class TStructField {
 public:

  TStructField(const TStructField&);
  TStructField& operator=(const TStructField&);
  TStructField() : name(), comment() {
  }

  virtual ~TStructField() throw();
  std::string name;
  std::string comment;

  _TStructField__isset __isset;

  void __set_name(const std::string& val);

  void __set_comment(const std::string& val);

  bool operator == (const TStructField & rhs) const
  {
    if (!(name == rhs.name))
      return false;
    if (__isset.comment != rhs.__isset.comment)
      return false;
    else if (__isset.comment && !(comment == rhs.comment))
      return false;
    return true;
  }
  bool operator != (const TStructField &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TStructField & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TStructField &a, TStructField &b);

inline std::ostream& operator<<(std::ostream& out, const TStructField& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _TTypeNode__isset {
  _TTypeNode__isset() : scalar_type(false), struct_fields(false) {}
  bool scalar_type :1;
  bool struct_fields :1;
} _TTypeNode__isset;

class TTypeNode {
 public:

  TTypeNode(const TTypeNode&);
  TTypeNode& operator=(const TTypeNode&);
  TTypeNode() : type((TTypeNodeType::type)0) {
  }

  virtual ~TTypeNode() throw();
  TTypeNodeType::type type;
  TScalarType scalar_type;
  std::vector<TStructField>  struct_fields;

  _TTypeNode__isset __isset;

  void __set_type(const TTypeNodeType::type val);

  void __set_scalar_type(const TScalarType& val);

  void __set_struct_fields(const std::vector<TStructField> & val);

  bool operator == (const TTypeNode & rhs) const
  {
    if (!(type == rhs.type))
      return false;
    if (__isset.scalar_type != rhs.__isset.scalar_type)
      return false;
    else if (__isset.scalar_type && !(scalar_type == rhs.scalar_type))
      return false;
    if (__isset.struct_fields != rhs.__isset.struct_fields)
      return false;
    else if (__isset.struct_fields && !(struct_fields == rhs.struct_fields))
      return false;
    return true;
  }
  bool operator != (const TTypeNode &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TTypeNode & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TTypeNode &a, TTypeNode &b);

inline std::ostream& operator<<(std::ostream& out, const TTypeNode& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _TColumnType__isset {
  _TColumnType__isset() : types(false) {}
  bool types :1;
} _TColumnType__isset;

class TColumnType {
 public:

  TColumnType(const TColumnType&);
  TColumnType& operator=(const TColumnType&);
  TColumnType() {
  }

  virtual ~TColumnType() throw();
  std::vector<TTypeNode>  types;

  _TColumnType__isset __isset;

  void __set_types(const std::vector<TTypeNode> & val);

  bool operator == (const TColumnType & rhs) const
  {
    if (!(types == rhs.types))
      return false;
    return true;
  }
  bool operator != (const TColumnType &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TColumnType & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TColumnType &a, TColumnType &b);

inline std::ostream& operator<<(std::ostream& out, const TColumnType& obj)
{
  obj.printTo(out);
  return out;
}


class TNetworkAddress {
 public:

  TNetworkAddress(const TNetworkAddress&);
  TNetworkAddress& operator=(const TNetworkAddress&);
  TNetworkAddress() : hostname(), port(0) {
  }

  virtual ~TNetworkAddress() throw();
  std::string hostname;
  int32_t port;

  void __set_hostname(const std::string& val);

  void __set_port(const int32_t val);

  bool operator == (const TNetworkAddress & rhs) const
  {
    if (!(hostname == rhs.hostname))
      return false;
    if (!(port == rhs.port))
      return false;
    return true;
  }
  bool operator != (const TNetworkAddress &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TNetworkAddress & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TNetworkAddress &a, TNetworkAddress &b);

inline std::ostream& operator<<(std::ostream& out, const TNetworkAddress& obj)
{
  obj.printTo(out);
  return out;
}


class TUniqueId {
 public:

  TUniqueId(const TUniqueId&);
  TUniqueId& operator=(const TUniqueId&);
  TUniqueId() : hi(0), lo(0) {
  }

  virtual ~TUniqueId() throw();
  int64_t hi;
  int64_t lo;

  void __set_hi(const int64_t val);

  void __set_lo(const int64_t val);

  bool operator == (const TUniqueId & rhs) const
  {
    if (!(hi == rhs.hi))
      return false;
    if (!(lo == rhs.lo))
      return false;
    return true;
  }
  bool operator != (const TUniqueId &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TUniqueId & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TUniqueId &a, TUniqueId &b);

inline std::ostream& operator<<(std::ostream& out, const TUniqueId& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _TFunctionName__isset {
  _TFunctionName__isset() : db_name(false) {}
  bool db_name :1;
} _TFunctionName__isset;

class TFunctionName {
 public:

  TFunctionName(const TFunctionName&);
  TFunctionName& operator=(const TFunctionName&);
  TFunctionName() : db_name(), function_name() {
  }

  virtual ~TFunctionName() throw();
  std::string db_name;
  std::string function_name;

  _TFunctionName__isset __isset;

  void __set_db_name(const std::string& val);

  void __set_function_name(const std::string& val);

  bool operator == (const TFunctionName & rhs) const
  {
    if (__isset.db_name != rhs.__isset.db_name)
      return false;
    else if (__isset.db_name && !(db_name == rhs.db_name))
      return false;
    if (!(function_name == rhs.function_name))
      return false;
    return true;
  }
  bool operator != (const TFunctionName &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TFunctionName & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TFunctionName &a, TFunctionName &b);

inline std::ostream& operator<<(std::ostream& out, const TFunctionName& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _TScalarFunction__isset {
  _TScalarFunction__isset() : prepare_fn_symbol(false), close_fn_symbol(false) {}
  bool prepare_fn_symbol :1;
  bool close_fn_symbol :1;
} _TScalarFunction__isset;

class TScalarFunction {
 public:

  TScalarFunction(const TScalarFunction&);
  TScalarFunction& operator=(const TScalarFunction&);
  TScalarFunction() : symbol(), prepare_fn_symbol(), close_fn_symbol() {
  }

  virtual ~TScalarFunction() throw();
  std::string symbol;
  std::string prepare_fn_symbol;
  std::string close_fn_symbol;

  _TScalarFunction__isset __isset;

  void __set_symbol(const std::string& val);

  void __set_prepare_fn_symbol(const std::string& val);

  void __set_close_fn_symbol(const std::string& val);

  bool operator == (const TScalarFunction & rhs) const
  {
    if (!(symbol == rhs.symbol))
      return false;
    if (__isset.prepare_fn_symbol != rhs.__isset.prepare_fn_symbol)
      return false;
    else if (__isset.prepare_fn_symbol && !(prepare_fn_symbol == rhs.prepare_fn_symbol))
      return false;
    if (__isset.close_fn_symbol != rhs.__isset.close_fn_symbol)
      return false;
    else if (__isset.close_fn_symbol && !(close_fn_symbol == rhs.close_fn_symbol))
      return false;
    return true;
  }
  bool operator != (const TScalarFunction &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TScalarFunction & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TScalarFunction &a, TScalarFunction &b);

inline std::ostream& operator<<(std::ostream& out, const TScalarFunction& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _TAggregateFunction__isset {
  _TAggregateFunction__isset() : serialize_fn_symbol(false), merge_fn_symbol(false), finalize_fn_symbol(false), get_value_fn_symbol(false), remove_fn_symbol(false), ignores_distinct(false) {}
  bool serialize_fn_symbol :1;
  bool merge_fn_symbol :1;
  bool finalize_fn_symbol :1;
  bool get_value_fn_symbol :1;
  bool remove_fn_symbol :1;
  bool ignores_distinct :1;
} _TAggregateFunction__isset;

class TAggregateFunction {
 public:

  TAggregateFunction(const TAggregateFunction&);
  TAggregateFunction& operator=(const TAggregateFunction&);
  TAggregateFunction() : update_fn_symbol(), init_fn_symbol(), serialize_fn_symbol(), merge_fn_symbol(), finalize_fn_symbol(), get_value_fn_symbol(), remove_fn_symbol(), ignores_distinct(0) {
  }

  virtual ~TAggregateFunction() throw();
  TColumnType intermediate_type;
  std::string update_fn_symbol;
  std::string init_fn_symbol;
  std::string serialize_fn_symbol;
  std::string merge_fn_symbol;
  std::string finalize_fn_symbol;
  std::string get_value_fn_symbol;
  std::string remove_fn_symbol;
  bool ignores_distinct;

  _TAggregateFunction__isset __isset;

  void __set_intermediate_type(const TColumnType& val);

  void __set_update_fn_symbol(const std::string& val);

  void __set_init_fn_symbol(const std::string& val);

  void __set_serialize_fn_symbol(const std::string& val);

  void __set_merge_fn_symbol(const std::string& val);

  void __set_finalize_fn_symbol(const std::string& val);

  void __set_get_value_fn_symbol(const std::string& val);

  void __set_remove_fn_symbol(const std::string& val);

  void __set_ignores_distinct(const bool val);

  bool operator == (const TAggregateFunction & rhs) const
  {
    if (!(intermediate_type == rhs.intermediate_type))
      return false;
    if (!(update_fn_symbol == rhs.update_fn_symbol))
      return false;
    if (!(init_fn_symbol == rhs.init_fn_symbol))
      return false;
    if (__isset.serialize_fn_symbol != rhs.__isset.serialize_fn_symbol)
      return false;
    else if (__isset.serialize_fn_symbol && !(serialize_fn_symbol == rhs.serialize_fn_symbol))
      return false;
    if (__isset.merge_fn_symbol != rhs.__isset.merge_fn_symbol)
      return false;
    else if (__isset.merge_fn_symbol && !(merge_fn_symbol == rhs.merge_fn_symbol))
      return false;
    if (__isset.finalize_fn_symbol != rhs.__isset.finalize_fn_symbol)
      return false;
    else if (__isset.finalize_fn_symbol && !(finalize_fn_symbol == rhs.finalize_fn_symbol))
      return false;
    if (__isset.get_value_fn_symbol != rhs.__isset.get_value_fn_symbol)
      return false;
    else if (__isset.get_value_fn_symbol && !(get_value_fn_symbol == rhs.get_value_fn_symbol))
      return false;
    if (__isset.remove_fn_symbol != rhs.__isset.remove_fn_symbol)
      return false;
    else if (__isset.remove_fn_symbol && !(remove_fn_symbol == rhs.remove_fn_symbol))
      return false;
    if (__isset.ignores_distinct != rhs.__isset.ignores_distinct)
      return false;
    else if (__isset.ignores_distinct && !(ignores_distinct == rhs.ignores_distinct))
      return false;
    return true;
  }
  bool operator != (const TAggregateFunction &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TAggregateFunction & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TAggregateFunction &a, TAggregateFunction &b);

inline std::ostream& operator<<(std::ostream& out, const TAggregateFunction& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _TFunction__isset {
  _TFunction__isset() : comment(false), signature(false), hdfs_location(false), scalar_fn(false), aggregate_fn(false) {}
  bool comment :1;
  bool signature :1;
  bool hdfs_location :1;
  bool scalar_fn :1;
  bool aggregate_fn :1;
} _TFunction__isset;

class TFunction {
 public:

  TFunction(const TFunction&);
  TFunction& operator=(const TFunction&);
  TFunction() : binary_type((TFunctionBinaryType::type)0), has_var_args(0), comment(), signature(), hdfs_location(), is_persistent(0) {
  }

  virtual ~TFunction() throw();
  TFunctionName name;
  TFunctionBinaryType::type binary_type;
  std::vector<TColumnType>  arg_types;
  TColumnType ret_type;
  bool has_var_args;
  std::string comment;
  std::string signature;
  std::string hdfs_location;
  TScalarFunction scalar_fn;
  TAggregateFunction aggregate_fn;
  bool is_persistent;

  _TFunction__isset __isset;

  void __set_name(const TFunctionName& val);

  void __set_binary_type(const TFunctionBinaryType::type val);

  void __set_arg_types(const std::vector<TColumnType> & val);

  void __set_ret_type(const TColumnType& val);

  void __set_has_var_args(const bool val);

  void __set_comment(const std::string& val);

  void __set_signature(const std::string& val);

  void __set_hdfs_location(const std::string& val);

  void __set_scalar_fn(const TScalarFunction& val);

  void __set_aggregate_fn(const TAggregateFunction& val);

  void __set_is_persistent(const bool val);

  bool operator == (const TFunction & rhs) const
  {
    if (!(name == rhs.name))
      return false;
    if (!(binary_type == rhs.binary_type))
      return false;
    if (!(arg_types == rhs.arg_types))
      return false;
    if (!(ret_type == rhs.ret_type))
      return false;
    if (!(has_var_args == rhs.has_var_args))
      return false;
    if (__isset.comment != rhs.__isset.comment)
      return false;
    else if (__isset.comment && !(comment == rhs.comment))
      return false;
    if (__isset.signature != rhs.__isset.signature)
      return false;
    else if (__isset.signature && !(signature == rhs.signature))
      return false;
    if (__isset.hdfs_location != rhs.__isset.hdfs_location)
      return false;
    else if (__isset.hdfs_location && !(hdfs_location == rhs.hdfs_location))
      return false;
    if (__isset.scalar_fn != rhs.__isset.scalar_fn)
      return false;
    else if (__isset.scalar_fn && !(scalar_fn == rhs.scalar_fn))
      return false;
    if (__isset.aggregate_fn != rhs.__isset.aggregate_fn)
      return false;
    else if (__isset.aggregate_fn && !(aggregate_fn == rhs.aggregate_fn))
      return false;
    if (!(is_persistent == rhs.is_persistent))
      return false;
    return true;
  }
  bool operator != (const TFunction &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TFunction & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(TFunction &a, TFunction &b);

inline std::ostream& operator<<(std::ostream& out, const TFunction& obj)
{
  obj.printTo(out);
  return out;
}

} // namespace

#endif