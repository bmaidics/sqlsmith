/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef beeswax_TYPES_H
#define beeswax_TYPES_H

#include <iosfwd>

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>
#include "hive_metastore_types.h"


namespace beeswax {

struct QueryState {
  enum type {
    CREATED = 0,
    INITIALIZED = 1,
    COMPILED = 2,
    RUNNING = 3,
    FINISHED = 4,
    EXCEPTION = 5
  };
};

extern const std::map<int, const char*> _QueryState_VALUES_TO_NAMES;

typedef std::string LogContextId;

class Query;

class QueryHandle;

class QueryExplanation;

class Results;

class ResultsMetadata;

class BeeswaxException;

class QueryNotFoundException;

class ConfigVariable;

typedef struct _Query__isset {
  _Query__isset() : query(false), configuration(false), hadoop_user(false) {}
  bool query :1;
  bool configuration :1;
  bool hadoop_user :1;
} _Query__isset;

class Query {
 public:

  Query(const Query&);
  Query& operator=(const Query&);
  Query() : query(), hadoop_user() {
  }

  virtual ~Query() throw();
  std::string query;
  std::vector<std::string>  configuration;
  std::string hadoop_user;

  _Query__isset __isset;

  void __set_query(const std::string& val);

  void __set_configuration(const std::vector<std::string> & val);

  void __set_hadoop_user(const std::string& val);

  bool operator == (const Query & rhs) const
  {
    if (!(query == rhs.query))
      return false;
    if (!(configuration == rhs.configuration))
      return false;
    if (!(hadoop_user == rhs.hadoop_user))
      return false;
    return true;
  }
  bool operator != (const Query &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Query & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(Query &a, Query &b);

inline std::ostream& operator<<(std::ostream& out, const Query& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _QueryHandle__isset {
  _QueryHandle__isset() : id(false), log_context(false) {}
  bool id :1;
  bool log_context :1;
} _QueryHandle__isset;

class QueryHandle {
 public:

  QueryHandle(const QueryHandle&);
  QueryHandle& operator=(const QueryHandle&);
  QueryHandle() : id(), log_context() {
  }

  virtual ~QueryHandle() throw();
  std::string id;
  LogContextId log_context;

  _QueryHandle__isset __isset;

  void __set_id(const std::string& val);

  void __set_log_context(const LogContextId& val);

  bool operator == (const QueryHandle & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(log_context == rhs.log_context))
      return false;
    return true;
  }
  bool operator != (const QueryHandle &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const QueryHandle & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(QueryHandle &a, QueryHandle &b);

inline std::ostream& operator<<(std::ostream& out, const QueryHandle& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _QueryExplanation__isset {
  _QueryExplanation__isset() : textual(false) {}
  bool textual :1;
} _QueryExplanation__isset;

class QueryExplanation {
 public:

  QueryExplanation(const QueryExplanation&);
  QueryExplanation& operator=(const QueryExplanation&);
  QueryExplanation() : textual() {
  }

  virtual ~QueryExplanation() throw();
  std::string textual;

  _QueryExplanation__isset __isset;

  void __set_textual(const std::string& val);

  bool operator == (const QueryExplanation & rhs) const
  {
    if (!(textual == rhs.textual))
      return false;
    return true;
  }
  bool operator != (const QueryExplanation &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const QueryExplanation & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(QueryExplanation &a, QueryExplanation &b);

inline std::ostream& operator<<(std::ostream& out, const QueryExplanation& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _Results__isset {
  _Results__isset() : ready(false), columns(false), data(false), start_row(false), has_more(false) {}
  bool ready :1;
  bool columns :1;
  bool data :1;
  bool start_row :1;
  bool has_more :1;
} _Results__isset;

class Results {
 public:

  Results(const Results&);
  Results& operator=(const Results&);
  Results() : ready(0), start_row(0), has_more(0) {
  }

  virtual ~Results() throw();
  bool ready;
  std::vector<std::string>  columns;
  std::vector<std::string>  data;
  int64_t start_row;
  bool has_more;

  _Results__isset __isset;

  void __set_ready(const bool val);

  void __set_columns(const std::vector<std::string> & val);

  void __set_data(const std::vector<std::string> & val);

  void __set_start_row(const int64_t val);

  void __set_has_more(const bool val);

  bool operator == (const Results & rhs) const
  {
    if (!(ready == rhs.ready))
      return false;
    if (!(columns == rhs.columns))
      return false;
    if (!(data == rhs.data))
      return false;
    if (!(start_row == rhs.start_row))
      return false;
    if (!(has_more == rhs.has_more))
      return false;
    return true;
  }
  bool operator != (const Results &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Results & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(Results &a, Results &b);

inline std::ostream& operator<<(std::ostream& out, const Results& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _ResultsMetadata__isset {
  _ResultsMetadata__isset() : schema(false), table_dir(false), in_tablename(false), delim(false) {}
  bool schema :1;
  bool table_dir :1;
  bool in_tablename :1;
  bool delim :1;
} _ResultsMetadata__isset;

class ResultsMetadata {
 public:

  ResultsMetadata(const ResultsMetadata&);
  ResultsMetadata& operator=(const ResultsMetadata&);
  ResultsMetadata() : table_dir(), in_tablename(), delim() {
  }

  virtual ~ResultsMetadata() throw();
   ::Apache::Hadoop::Hive::Schema schema;
  std::string table_dir;
  std::string in_tablename;
  std::string delim;

  _ResultsMetadata__isset __isset;

  void __set_schema(const  ::Apache::Hadoop::Hive::Schema& val);

  void __set_table_dir(const std::string& val);

  void __set_in_tablename(const std::string& val);

  void __set_delim(const std::string& val);

  bool operator == (const ResultsMetadata & rhs) const
  {
    if (!(schema == rhs.schema))
      return false;
    if (!(table_dir == rhs.table_dir))
      return false;
    if (!(in_tablename == rhs.in_tablename))
      return false;
    if (!(delim == rhs.delim))
      return false;
    return true;
  }
  bool operator != (const ResultsMetadata &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ResultsMetadata & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(ResultsMetadata &a, ResultsMetadata &b);

inline std::ostream& operator<<(std::ostream& out, const ResultsMetadata& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _BeeswaxException__isset {
  _BeeswaxException__isset() : message(false), log_context(false), handle(false), errorCode(true), SQLState(true) {}
  bool message :1;
  bool log_context :1;
  bool handle :1;
  bool errorCode :1;
  bool SQLState :1;
} _BeeswaxException__isset;

class BeeswaxException : public ::apache::thrift::TException {
 public:

  BeeswaxException(const BeeswaxException&);
  BeeswaxException& operator=(const BeeswaxException&);
  BeeswaxException() : message(), log_context(), errorCode(0), SQLState("     ") {
  }

  virtual ~BeeswaxException() throw();
  std::string message;
  LogContextId log_context;
  QueryHandle handle;
  int32_t errorCode;
  std::string SQLState;

  _BeeswaxException__isset __isset;

  void __set_message(const std::string& val);

  void __set_log_context(const LogContextId& val);

  void __set_handle(const QueryHandle& val);

  void __set_errorCode(const int32_t val);

  void __set_SQLState(const std::string& val);

  bool operator == (const BeeswaxException & rhs) const
  {
    if (!(message == rhs.message))
      return false;
    if (!(log_context == rhs.log_context))
      return false;
    if (!(handle == rhs.handle))
      return false;
    if (__isset.errorCode != rhs.__isset.errorCode)
      return false;
    else if (__isset.errorCode && !(errorCode == rhs.errorCode))
      return false;
    if (__isset.SQLState != rhs.__isset.SQLState)
      return false;
    else if (__isset.SQLState && !(SQLState == rhs.SQLState))
      return false;
    return true;
  }
  bool operator != (const BeeswaxException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const BeeswaxException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const throw();
};

void swap(BeeswaxException &a, BeeswaxException &b);

inline std::ostream& operator<<(std::ostream& out, const BeeswaxException& obj)
{
  obj.printTo(out);
  return out;
}


class QueryNotFoundException : public ::apache::thrift::TException {
 public:

  QueryNotFoundException(const QueryNotFoundException&);
  QueryNotFoundException& operator=(const QueryNotFoundException&);
  QueryNotFoundException() {
  }

  virtual ~QueryNotFoundException() throw();

  bool operator == (const QueryNotFoundException & /* rhs */) const
  {
    return true;
  }
  bool operator != (const QueryNotFoundException &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const QueryNotFoundException & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
  mutable std::string thriftTExceptionMessageHolder_;
  const char* what() const throw();
};

void swap(QueryNotFoundException &a, QueryNotFoundException &b);

inline std::ostream& operator<<(std::ostream& out, const QueryNotFoundException& obj)
{
  obj.printTo(out);
  return out;
}

typedef struct _ConfigVariable__isset {
  _ConfigVariable__isset() : key(false), value(false), description(false) {}
  bool key :1;
  bool value :1;
  bool description :1;
} _ConfigVariable__isset;

class ConfigVariable {
 public:

  ConfigVariable(const ConfigVariable&);
  ConfigVariable& operator=(const ConfigVariable&);
  ConfigVariable() : key(), value(), description() {
  }

  virtual ~ConfigVariable() throw();
  std::string key;
  std::string value;
  std::string description;

  _ConfigVariable__isset __isset;

  void __set_key(const std::string& val);

  void __set_value(const std::string& val);

  void __set_description(const std::string& val);

  bool operator == (const ConfigVariable & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    if (!(value == rhs.value))
      return false;
    if (!(description == rhs.description))
      return false;
    return true;
  }
  bool operator != (const ConfigVariable &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ConfigVariable & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

  virtual void printTo(std::ostream& out) const;
};

void swap(ConfigVariable &a, ConfigVariable &b);

inline std::ostream& operator<<(std::ostream& out, const ConfigVariable& obj)
{
  obj.printTo(out);
  return out;
}

} // namespace

#endif
