/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef KeyValueStore_TYPES_H
#define KeyValueStore_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>



namespace KeyValueStore {

struct KVStoreStatus {
  enum type {
    OK = 1,
    EKEYNOTFOUND = 2,
    EITEMNOTFOUND = 3,
    EPUTFAILED = 4,
    EITEMEXISTS = 5,
    INTERNAL_FAILURE = 6,
    NOT_IMPLEMENTED = 7
  };
};

extern const std::map<int, const char*> _KVStoreStatus_VALUES_TO_NAMES;

typedef struct _GetResponse__isset {
  _GetResponse__isset() : status(false), value(false), timestamp(false) {}
  bool status;
  bool value;
  bool timestamp;
} _GetResponse__isset;

class GetResponse {
 public:

  static const char* ascii_fingerprint; // = "EC9673EEAE3E5A373D15AC0EC614F2A0";
  static const uint8_t binary_fingerprint[16]; // = {0xEC,0x96,0x73,0xEE,0xAE,0x3E,0x5A,0x37,0x3D,0x15,0xAC,0x0E,0xC6,0x14,0xF2,0xA0};

  GetResponse() : status((KVStoreStatus::type)0), value() {
  }

  virtual ~GetResponse() throw() {}

  KVStoreStatus::type status;
  std::string value;
  std::vector<int64_t>  timestamp;

  _GetResponse__isset __isset;

  void __set_status(const KVStoreStatus::type val) {
    status = val;
  }

  void __set_value(const std::string& val) {
    value = val;
  }

  void __set_timestamp(const std::vector<int64_t> & val) {
    timestamp = val;
  }

  bool operator == (const GetResponse & rhs) const
  {
    if (!(status == rhs.status))
      return false;
    if (!(value == rhs.value))
      return false;
    if (!(timestamp == rhs.timestamp))
      return false;
    return true;
  }
  bool operator != (const GetResponse &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const GetResponse & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(GetResponse &a, GetResponse &b);

typedef struct _GetListResponse__isset {
  _GetListResponse__isset() : status(false), values(false) {}
  bool status;
  bool values;
} _GetListResponse__isset;

class GetListResponse {
 public:

  static const char* ascii_fingerprint; // = "A22BE3E84688C9DA4E00CC902B4EE818";
  static const uint8_t binary_fingerprint[16]; // = {0xA2,0x2B,0xE3,0xE8,0x46,0x88,0xC9,0xDA,0x4E,0x00,0xCC,0x90,0x2B,0x4E,0xE8,0x18};

  GetListResponse() : status((KVStoreStatus::type)0) {
  }

  virtual ~GetListResponse() throw() {}

  KVStoreStatus::type status;
  std::vector<std::string>  values;

  _GetListResponse__isset __isset;

  void __set_status(const KVStoreStatus::type val) {
    status = val;
  }

  void __set_values(const std::vector<std::string> & val) {
    values = val;
  }

  bool operator == (const GetListResponse & rhs) const
  {
    if (!(status == rhs.status))
      return false;
    if (!(values == rhs.values))
      return false;
    return true;
  }
  bool operator != (const GetListResponse &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const GetListResponse & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(GetListResponse &a, GetListResponse &b);

} // namespace

#endif
