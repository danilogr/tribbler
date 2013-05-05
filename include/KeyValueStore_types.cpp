/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "KeyValueStore_types.h"

#include <algorithm>

namespace KeyValueStore {

int _kKVStoreStatusValues[] = {
  KVStoreStatus::OK,
  KVStoreStatus::EKEYNOTFOUND,
  KVStoreStatus::EITEMNOTFOUND,
  KVStoreStatus::EPUTFAILED,
  KVStoreStatus::EITEMEXISTS,
  KVStoreStatus::INTERNAL_FAILURE,
  KVStoreStatus::NOT_IMPLEMENTED
};
const char* _kKVStoreStatusNames[] = {
  "OK",
  "EKEYNOTFOUND",
  "EITEMNOTFOUND",
  "EPUTFAILED",
  "EITEMEXISTS",
  "INTERNAL_FAILURE",
  "NOT_IMPLEMENTED"
};
const std::map<int, const char*> _KVStoreStatus_VALUES_TO_NAMES(::apache::thrift::TEnumIterator(7, _kKVStoreStatusValues, _kKVStoreStatusNames), ::apache::thrift::TEnumIterator(-1, NULL, NULL));

const char* GetResponse::ascii_fingerprint = "EC9673EEAE3E5A373D15AC0EC614F2A0";
const uint8_t GetResponse::binary_fingerprint[16] = {0xEC,0x96,0x73,0xEE,0xAE,0x3E,0x5A,0x37,0x3D,0x15,0xAC,0x0E,0xC6,0x14,0xF2,0xA0};

uint32_t GetResponse::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


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
          this->status = (KVStoreStatus::type)ecast0;
          this->__isset.status = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->value);
          this->__isset.value = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->timestamp.clear();
            uint32_t _size1;
            ::apache::thrift::protocol::TType _etype4;
            xfer += iprot->readListBegin(_etype4, _size1);
            this->timestamp.resize(_size1);
            uint32_t _i5;
            for (_i5 = 0; _i5 < _size1; ++_i5)
            {
              xfer += iprot->readI64(this->timestamp[_i5]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.timestamp = true;
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

  return xfer;
}

uint32_t GetResponse::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("GetResponse");

  xfer += oprot->writeFieldBegin("status", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32((int32_t)this->status);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("value", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->value);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("timestamp", ::apache::thrift::protocol::T_LIST, 3);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_I64, static_cast<uint32_t>(this->timestamp.size()));
    std::vector<int64_t> ::const_iterator _iter6;
    for (_iter6 = this->timestamp.begin(); _iter6 != this->timestamp.end(); ++_iter6)
    {
      xfer += oprot->writeI64((*_iter6));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(GetResponse &a, GetResponse &b) {
  using ::std::swap;
  swap(a.status, b.status);
  swap(a.value, b.value);
  swap(a.timestamp, b.timestamp);
  swap(a.__isset, b.__isset);
}

const char* GetListResponse::ascii_fingerprint = "A22BE3E84688C9DA4E00CC902B4EE818";
const uint8_t GetListResponse::binary_fingerprint[16] = {0xA2,0x2B,0xE3,0xE8,0x46,0x88,0xC9,0xDA,0x4E,0x00,0xCC,0x90,0x2B,0x4E,0xE8,0x18};

uint32_t GetListResponse::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


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
          int32_t ecast7;
          xfer += iprot->readI32(ecast7);
          this->status = (KVStoreStatus::type)ecast7;
          this->__isset.status = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->values.clear();
            uint32_t _size8;
            ::apache::thrift::protocol::TType _etype11;
            xfer += iprot->readListBegin(_etype11, _size8);
            this->values.resize(_size8);
            uint32_t _i12;
            for (_i12 = 0; _i12 < _size8; ++_i12)
            {
              xfer += iprot->readString(this->values[_i12]);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.values = true;
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

  return xfer;
}

uint32_t GetListResponse::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("GetListResponse");

  xfer += oprot->writeFieldBegin("status", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32((int32_t)this->status);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("values", ::apache::thrift::protocol::T_LIST, 2);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRING, static_cast<uint32_t>(this->values.size()));
    std::vector<std::string> ::const_iterator _iter13;
    for (_iter13 = this->values.begin(); _iter13 != this->values.end(); ++_iter13)
    {
      xfer += oprot->writeString((*_iter13));
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(GetListResponse &a, GetListResponse &b) {
  using ::std::swap;
  swap(a.status, b.status);
  swap(a.values, b.values);
  swap(a.__isset, b.__isset);
}

} // namespace
