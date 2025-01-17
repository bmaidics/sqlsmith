/**
 * Autogenerated by Thrift Compiler (0.9.3)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "Status_types.h"

#include <algorithm>
#include <ostream>

#include <thrift/TToString.h>

namespace impala {


TStatus::~TStatus() throw() {
}


void TStatus::__set_status_code(const  ::impala::TErrorCode::type val) {
  this->status_code = val;
}

void TStatus::__set_error_msgs(const std::vector<std::string> & val) {
  this->error_msgs = val;
}

uint32_t TStatus::read(::apache::thrift::protocol::TProtocol* iprot) {

  apache::thrift::protocol::TInputRecursionTracker tracker(*iprot);
  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;

  bool isset_status_code = false;

  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          int32_t ecast0;
          xfer += iprot->readI32(ecast0);
          this->status_code = ( ::impala::TErrorCode::type)ecast0;
          isset_status_code = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->error_msgs.clear();
            uint32_t _size1;
            ::apache::thrift::protocol::TType _etype4;
            xfer += iprot->readListBegin(_etype4, _size1);
            this->error_msgs.resize(_size1);
            uint32_t _i5;
            for (_i5 = 0; _i5 < _size1; ++_i5)
            {
              xfer += iprot->readString(this->error_msgs[_i5]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.error_msgs = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  if (!isset_status_code)
    throw TProtocolException(TProtocolException::INVALID_DATA);
  return xfer;
}

uint32_t TStatus::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  apache::thrift::protocol::TOutputRecursionTracker tracker(*oprot);
  xfer += oprot->writeStructBegin("TStatus");

  xfer += oprot->writeFieldBegin("status_code", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32((int32_t)this->status_code);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("error_msgs", ::apache::thrift::protocol::T_LIST, 2);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->error_msgs.size()));
    std::vector<std::string> ::const_iterator _iter6;
    for (_iter6 = this->error_msgs.begin(); _iter6 != this->error_msgs.end(); ++_iter6)
    {
      xfer += oprot->writeString((*_iter6));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(TStatus &a, TStatus &b) {
  using ::std::swap;
  swap(a.status_code, b.status_code);
  swap(a.error_msgs, b.error_msgs);
  swap(a.__isset, b.__isset);
}

TStatus::TStatus(const TStatus& other7) {
  status_code = other7.status_code;
  error_msgs = other7.error_msgs;
  __isset = other7.__isset;
}
TStatus& TStatus::operator=(const TStatus& other8) {
  status_code = other8.status_code;
  error_msgs = other8.error_msgs;
  __isset = other8.__isset;
  return *this;
}
void TStatus::printTo(std::ostream& out) const {
  using ::apache::thrift::to_string;
  out << "TStatus(";
  out << "status_code=" << to_string(status_code);
  out << ", " << "error_msgs=" << to_string(error_msgs);
  out << ")";
}

} // namespace
