/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef KeyValueStore_H
#define KeyValueStore_H

#include <thrift/TDispatchProcessor.h>
#include "KeyValueStore_types.h"

namespace KeyValueStore {

class KeyValueStoreIf {
 public:
  virtual ~KeyValueStoreIf() {}
  virtual void Get(GetResponse& _return, const std::string& key) = 0;
  virtual void GetList(GetListResponse& _return, const std::string& key) = 0;
  virtual KVStoreStatus::type Put(const std::string& key, const std::string& value, const std::string& clientid) = 0;
  virtual KVStoreStatus::type AddToList(const std::string& key, const std::string& value, const std::string& clientid) = 0;
  virtual KVStoreStatus::type RemoveFromList(const std::string& key, const std::string& value, const std::string& clientid) = 0;
  virtual KVStoreStatus::type Eval(const std::string& counter_key, const std::string& user_post, const std::string& user_list, const std::string& clientid) = 0;
  virtual void KVPut(const std::string& key, const std::string& value, const std::string& clientid) = 0;
  virtual void KVAddToList(const std::string& key, const std::string& value, const std::string& clientid) = 0;
  virtual void KVRemoveFromList(const std::string& key, const std::string& value, const std::string& clientid) = 0;
  virtual void KVEval(const std::string& counter_key, const std::string& user_post, const std::string& user_list, const std::string& clientid, const std::vector<int64_t> & timestamp) = 0;
};

class KeyValueStoreIfFactory {
 public:
  typedef KeyValueStoreIf Handler;

  virtual ~KeyValueStoreIfFactory() {}

  virtual KeyValueStoreIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(KeyValueStoreIf* /* handler */) = 0;
};

class KeyValueStoreIfSingletonFactory : virtual public KeyValueStoreIfFactory {
 public:
  KeyValueStoreIfSingletonFactory(const boost::shared_ptr<KeyValueStoreIf>& iface) : iface_(iface) {}
  virtual ~KeyValueStoreIfSingletonFactory() {}

  virtual KeyValueStoreIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(KeyValueStoreIf* /* handler */) {}

 protected:
  boost::shared_ptr<KeyValueStoreIf> iface_;
};

class KeyValueStoreNull : virtual public KeyValueStoreIf {
 public:
  virtual ~KeyValueStoreNull() {}
  void Get(GetResponse& /* _return */, const std::string& /* key */) {
    return;
  }
  void GetList(GetListResponse& /* _return */, const std::string& /* key */) {
    return;
  }
  KVStoreStatus::type Put(const std::string& /* key */, const std::string& /* value */, const std::string& /* clientid */) {
    KVStoreStatus::type _return = (KVStoreStatus::type)0;
    return _return;
  }
  KVStoreStatus::type AddToList(const std::string& /* key */, const std::string& /* value */, const std::string& /* clientid */) {
    KVStoreStatus::type _return = (KVStoreStatus::type)0;
    return _return;
  }
  KVStoreStatus::type RemoveFromList(const std::string& /* key */, const std::string& /* value */, const std::string& /* clientid */) {
    KVStoreStatus::type _return = (KVStoreStatus::type)0;
    return _return;
  }
  KVStoreStatus::type Eval(const std::string& /* counter_key */, const std::string& /* user_post */, const std::string& /* user_list */, const std::string& /* clientid */) {
    KVStoreStatus::type _return = (KVStoreStatus::type)0;
    return _return;
  }
  void KVPut(const std::string& /* key */, const std::string& /* value */, const std::string& /* clientid */) {
    return;
  }
  void KVAddToList(const std::string& /* key */, const std::string& /* value */, const std::string& /* clientid */) {
    return;
  }
  void KVRemoveFromList(const std::string& /* key */, const std::string& /* value */, const std::string& /* clientid */) {
    return;
  }
  void KVEval(const std::string& /* counter_key */, const std::string& /* user_post */, const std::string& /* user_list */, const std::string& /* clientid */, const std::vector<int64_t> & /* timestamp */) {
    return;
  }
};

typedef struct _KeyValueStore_Get_args__isset {
  _KeyValueStore_Get_args__isset() : key(false) {}
  bool key;
} _KeyValueStore_Get_args__isset;

class KeyValueStore_Get_args {
 public:

  KeyValueStore_Get_args() : key() {
  }

  virtual ~KeyValueStore_Get_args() throw() {}

  std::string key;

  _KeyValueStore_Get_args__isset __isset;

  void __set_key(const std::string& val) {
    key = val;
  }

  bool operator == (const KeyValueStore_Get_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_Get_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_Get_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_Get_pargs {
 public:


  virtual ~KeyValueStore_Get_pargs() throw() {}

  const std::string* key;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_Get_result__isset {
  _KeyValueStore_Get_result__isset() : success(false) {}
  bool success;
} _KeyValueStore_Get_result__isset;

class KeyValueStore_Get_result {
 public:

  KeyValueStore_Get_result() {
  }

  virtual ~KeyValueStore_Get_result() throw() {}

  GetResponse success;

  _KeyValueStore_Get_result__isset __isset;

  void __set_success(const GetResponse& val) {
    success = val;
  }

  bool operator == (const KeyValueStore_Get_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_Get_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_Get_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_Get_presult__isset {
  _KeyValueStore_Get_presult__isset() : success(false) {}
  bool success;
} _KeyValueStore_Get_presult__isset;

class KeyValueStore_Get_presult {
 public:


  virtual ~KeyValueStore_Get_presult() throw() {}

  GetResponse* success;

  _KeyValueStore_Get_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _KeyValueStore_GetList_args__isset {
  _KeyValueStore_GetList_args__isset() : key(false) {}
  bool key;
} _KeyValueStore_GetList_args__isset;

class KeyValueStore_GetList_args {
 public:

  KeyValueStore_GetList_args() : key() {
  }

  virtual ~KeyValueStore_GetList_args() throw() {}

  std::string key;

  _KeyValueStore_GetList_args__isset __isset;

  void __set_key(const std::string& val) {
    key = val;
  }

  bool operator == (const KeyValueStore_GetList_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_GetList_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_GetList_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_GetList_pargs {
 public:


  virtual ~KeyValueStore_GetList_pargs() throw() {}

  const std::string* key;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_GetList_result__isset {
  _KeyValueStore_GetList_result__isset() : success(false) {}
  bool success;
} _KeyValueStore_GetList_result__isset;

class KeyValueStore_GetList_result {
 public:

  KeyValueStore_GetList_result() {
  }

  virtual ~KeyValueStore_GetList_result() throw() {}

  GetListResponse success;

  _KeyValueStore_GetList_result__isset __isset;

  void __set_success(const GetListResponse& val) {
    success = val;
  }

  bool operator == (const KeyValueStore_GetList_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_GetList_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_GetList_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_GetList_presult__isset {
  _KeyValueStore_GetList_presult__isset() : success(false) {}
  bool success;
} _KeyValueStore_GetList_presult__isset;

class KeyValueStore_GetList_presult {
 public:


  virtual ~KeyValueStore_GetList_presult() throw() {}

  GetListResponse* success;

  _KeyValueStore_GetList_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _KeyValueStore_Put_args__isset {
  _KeyValueStore_Put_args__isset() : key(false), value(false), clientid(false) {}
  bool key;
  bool value;
  bool clientid;
} _KeyValueStore_Put_args__isset;

class KeyValueStore_Put_args {
 public:

  KeyValueStore_Put_args() : key(), value(), clientid() {
  }

  virtual ~KeyValueStore_Put_args() throw() {}

  std::string key;
  std::string value;
  std::string clientid;

  _KeyValueStore_Put_args__isset __isset;

  void __set_key(const std::string& val) {
    key = val;
  }

  void __set_value(const std::string& val) {
    value = val;
  }

  void __set_clientid(const std::string& val) {
    clientid = val;
  }

  bool operator == (const KeyValueStore_Put_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    if (!(value == rhs.value))
      return false;
    if (!(clientid == rhs.clientid))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_Put_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_Put_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_Put_pargs {
 public:


  virtual ~KeyValueStore_Put_pargs() throw() {}

  const std::string* key;
  const std::string* value;
  const std::string* clientid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_Put_result__isset {
  _KeyValueStore_Put_result__isset() : success(false) {}
  bool success;
} _KeyValueStore_Put_result__isset;

class KeyValueStore_Put_result {
 public:

  KeyValueStore_Put_result() : success((KVStoreStatus::type)0) {
  }

  virtual ~KeyValueStore_Put_result() throw() {}

  KVStoreStatus::type success;

  _KeyValueStore_Put_result__isset __isset;

  void __set_success(const KVStoreStatus::type val) {
    success = val;
  }

  bool operator == (const KeyValueStore_Put_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_Put_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_Put_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_Put_presult__isset {
  _KeyValueStore_Put_presult__isset() : success(false) {}
  bool success;
} _KeyValueStore_Put_presult__isset;

class KeyValueStore_Put_presult {
 public:


  virtual ~KeyValueStore_Put_presult() throw() {}

  KVStoreStatus::type* success;

  _KeyValueStore_Put_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _KeyValueStore_AddToList_args__isset {
  _KeyValueStore_AddToList_args__isset() : key(false), value(false), clientid(false) {}
  bool key;
  bool value;
  bool clientid;
} _KeyValueStore_AddToList_args__isset;

class KeyValueStore_AddToList_args {
 public:

  KeyValueStore_AddToList_args() : key(), value(), clientid() {
  }

  virtual ~KeyValueStore_AddToList_args() throw() {}

  std::string key;
  std::string value;
  std::string clientid;

  _KeyValueStore_AddToList_args__isset __isset;

  void __set_key(const std::string& val) {
    key = val;
  }

  void __set_value(const std::string& val) {
    value = val;
  }

  void __set_clientid(const std::string& val) {
    clientid = val;
  }

  bool operator == (const KeyValueStore_AddToList_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    if (!(value == rhs.value))
      return false;
    if (!(clientid == rhs.clientid))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_AddToList_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_AddToList_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_AddToList_pargs {
 public:


  virtual ~KeyValueStore_AddToList_pargs() throw() {}

  const std::string* key;
  const std::string* value;
  const std::string* clientid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_AddToList_result__isset {
  _KeyValueStore_AddToList_result__isset() : success(false) {}
  bool success;
} _KeyValueStore_AddToList_result__isset;

class KeyValueStore_AddToList_result {
 public:

  KeyValueStore_AddToList_result() : success((KVStoreStatus::type)0) {
  }

  virtual ~KeyValueStore_AddToList_result() throw() {}

  KVStoreStatus::type success;

  _KeyValueStore_AddToList_result__isset __isset;

  void __set_success(const KVStoreStatus::type val) {
    success = val;
  }

  bool operator == (const KeyValueStore_AddToList_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_AddToList_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_AddToList_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_AddToList_presult__isset {
  _KeyValueStore_AddToList_presult__isset() : success(false) {}
  bool success;
} _KeyValueStore_AddToList_presult__isset;

class KeyValueStore_AddToList_presult {
 public:


  virtual ~KeyValueStore_AddToList_presult() throw() {}

  KVStoreStatus::type* success;

  _KeyValueStore_AddToList_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _KeyValueStore_RemoveFromList_args__isset {
  _KeyValueStore_RemoveFromList_args__isset() : key(false), value(false), clientid(false) {}
  bool key;
  bool value;
  bool clientid;
} _KeyValueStore_RemoveFromList_args__isset;

class KeyValueStore_RemoveFromList_args {
 public:

  KeyValueStore_RemoveFromList_args() : key(), value(), clientid() {
  }

  virtual ~KeyValueStore_RemoveFromList_args() throw() {}

  std::string key;
  std::string value;
  std::string clientid;

  _KeyValueStore_RemoveFromList_args__isset __isset;

  void __set_key(const std::string& val) {
    key = val;
  }

  void __set_value(const std::string& val) {
    value = val;
  }

  void __set_clientid(const std::string& val) {
    clientid = val;
  }

  bool operator == (const KeyValueStore_RemoveFromList_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    if (!(value == rhs.value))
      return false;
    if (!(clientid == rhs.clientid))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_RemoveFromList_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_RemoveFromList_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_RemoveFromList_pargs {
 public:


  virtual ~KeyValueStore_RemoveFromList_pargs() throw() {}

  const std::string* key;
  const std::string* value;
  const std::string* clientid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_RemoveFromList_result__isset {
  _KeyValueStore_RemoveFromList_result__isset() : success(false) {}
  bool success;
} _KeyValueStore_RemoveFromList_result__isset;

class KeyValueStore_RemoveFromList_result {
 public:

  KeyValueStore_RemoveFromList_result() : success((KVStoreStatus::type)0) {
  }

  virtual ~KeyValueStore_RemoveFromList_result() throw() {}

  KVStoreStatus::type success;

  _KeyValueStore_RemoveFromList_result__isset __isset;

  void __set_success(const KVStoreStatus::type val) {
    success = val;
  }

  bool operator == (const KeyValueStore_RemoveFromList_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_RemoveFromList_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_RemoveFromList_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_RemoveFromList_presult__isset {
  _KeyValueStore_RemoveFromList_presult__isset() : success(false) {}
  bool success;
} _KeyValueStore_RemoveFromList_presult__isset;

class KeyValueStore_RemoveFromList_presult {
 public:


  virtual ~KeyValueStore_RemoveFromList_presult() throw() {}

  KVStoreStatus::type* success;

  _KeyValueStore_RemoveFromList_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _KeyValueStore_Eval_args__isset {
  _KeyValueStore_Eval_args__isset() : counter_key(false), user_post(false), user_list(false), clientid(false) {}
  bool counter_key;
  bool user_post;
  bool user_list;
  bool clientid;
} _KeyValueStore_Eval_args__isset;

class KeyValueStore_Eval_args {
 public:

  KeyValueStore_Eval_args() : counter_key(), user_post(), user_list(), clientid() {
  }

  virtual ~KeyValueStore_Eval_args() throw() {}

  std::string counter_key;
  std::string user_post;
  std::string user_list;
  std::string clientid;

  _KeyValueStore_Eval_args__isset __isset;

  void __set_counter_key(const std::string& val) {
    counter_key = val;
  }

  void __set_user_post(const std::string& val) {
    user_post = val;
  }

  void __set_user_list(const std::string& val) {
    user_list = val;
  }

  void __set_clientid(const std::string& val) {
    clientid = val;
  }

  bool operator == (const KeyValueStore_Eval_args & rhs) const
  {
    if (!(counter_key == rhs.counter_key))
      return false;
    if (!(user_post == rhs.user_post))
      return false;
    if (!(user_list == rhs.user_list))
      return false;
    if (!(clientid == rhs.clientid))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_Eval_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_Eval_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_Eval_pargs {
 public:


  virtual ~KeyValueStore_Eval_pargs() throw() {}

  const std::string* counter_key;
  const std::string* user_post;
  const std::string* user_list;
  const std::string* clientid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_Eval_result__isset {
  _KeyValueStore_Eval_result__isset() : success(false) {}
  bool success;
} _KeyValueStore_Eval_result__isset;

class KeyValueStore_Eval_result {
 public:

  KeyValueStore_Eval_result() : success((KVStoreStatus::type)0) {
  }

  virtual ~KeyValueStore_Eval_result() throw() {}

  KVStoreStatus::type success;

  _KeyValueStore_Eval_result__isset __isset;

  void __set_success(const KVStoreStatus::type val) {
    success = val;
  }

  bool operator == (const KeyValueStore_Eval_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_Eval_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_Eval_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_Eval_presult__isset {
  _KeyValueStore_Eval_presult__isset() : success(false) {}
  bool success;
} _KeyValueStore_Eval_presult__isset;

class KeyValueStore_Eval_presult {
 public:


  virtual ~KeyValueStore_Eval_presult() throw() {}

  KVStoreStatus::type* success;

  _KeyValueStore_Eval_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _KeyValueStore_KVPut_args__isset {
  _KeyValueStore_KVPut_args__isset() : key(false), value(false), clientid(false) {}
  bool key;
  bool value;
  bool clientid;
} _KeyValueStore_KVPut_args__isset;

class KeyValueStore_KVPut_args {
 public:

  KeyValueStore_KVPut_args() : key(), value(), clientid() {
  }

  virtual ~KeyValueStore_KVPut_args() throw() {}

  std::string key;
  std::string value;
  std::string clientid;

  _KeyValueStore_KVPut_args__isset __isset;

  void __set_key(const std::string& val) {
    key = val;
  }

  void __set_value(const std::string& val) {
    value = val;
  }

  void __set_clientid(const std::string& val) {
    clientid = val;
  }

  bool operator == (const KeyValueStore_KVPut_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    if (!(value == rhs.value))
      return false;
    if (!(clientid == rhs.clientid))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_KVPut_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_KVPut_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_KVPut_pargs {
 public:


  virtual ~KeyValueStore_KVPut_pargs() throw() {}

  const std::string* key;
  const std::string* value;
  const std::string* clientid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_KVAddToList_args__isset {
  _KeyValueStore_KVAddToList_args__isset() : key(false), value(false), clientid(false) {}
  bool key;
  bool value;
  bool clientid;
} _KeyValueStore_KVAddToList_args__isset;

class KeyValueStore_KVAddToList_args {
 public:

  KeyValueStore_KVAddToList_args() : key(), value(), clientid() {
  }

  virtual ~KeyValueStore_KVAddToList_args() throw() {}

  std::string key;
  std::string value;
  std::string clientid;

  _KeyValueStore_KVAddToList_args__isset __isset;

  void __set_key(const std::string& val) {
    key = val;
  }

  void __set_value(const std::string& val) {
    value = val;
  }

  void __set_clientid(const std::string& val) {
    clientid = val;
  }

  bool operator == (const KeyValueStore_KVAddToList_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    if (!(value == rhs.value))
      return false;
    if (!(clientid == rhs.clientid))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_KVAddToList_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_KVAddToList_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_KVAddToList_pargs {
 public:


  virtual ~KeyValueStore_KVAddToList_pargs() throw() {}

  const std::string* key;
  const std::string* value;
  const std::string* clientid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_KVRemoveFromList_args__isset {
  _KeyValueStore_KVRemoveFromList_args__isset() : key(false), value(false), clientid(false) {}
  bool key;
  bool value;
  bool clientid;
} _KeyValueStore_KVRemoveFromList_args__isset;

class KeyValueStore_KVRemoveFromList_args {
 public:

  KeyValueStore_KVRemoveFromList_args() : key(), value(), clientid() {
  }

  virtual ~KeyValueStore_KVRemoveFromList_args() throw() {}

  std::string key;
  std::string value;
  std::string clientid;

  _KeyValueStore_KVRemoveFromList_args__isset __isset;

  void __set_key(const std::string& val) {
    key = val;
  }

  void __set_value(const std::string& val) {
    value = val;
  }

  void __set_clientid(const std::string& val) {
    clientid = val;
  }

  bool operator == (const KeyValueStore_KVRemoveFromList_args & rhs) const
  {
    if (!(key == rhs.key))
      return false;
    if (!(value == rhs.value))
      return false;
    if (!(clientid == rhs.clientid))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_KVRemoveFromList_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_KVRemoveFromList_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_KVRemoveFromList_pargs {
 public:


  virtual ~KeyValueStore_KVRemoveFromList_pargs() throw() {}

  const std::string* key;
  const std::string* value;
  const std::string* clientid;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _KeyValueStore_KVEval_args__isset {
  _KeyValueStore_KVEval_args__isset() : counter_key(false), user_post(false), user_list(false), clientid(false), timestamp(false) {}
  bool counter_key;
  bool user_post;
  bool user_list;
  bool clientid;
  bool timestamp;
} _KeyValueStore_KVEval_args__isset;

class KeyValueStore_KVEval_args {
 public:

  KeyValueStore_KVEval_args() : counter_key(), user_post(), user_list(), clientid() {
  }

  virtual ~KeyValueStore_KVEval_args() throw() {}

  std::string counter_key;
  std::string user_post;
  std::string user_list;
  std::string clientid;
  std::vector<int64_t>  timestamp;

  _KeyValueStore_KVEval_args__isset __isset;

  void __set_counter_key(const std::string& val) {
    counter_key = val;
  }

  void __set_user_post(const std::string& val) {
    user_post = val;
  }

  void __set_user_list(const std::string& val) {
    user_list = val;
  }

  void __set_clientid(const std::string& val) {
    clientid = val;
  }

  void __set_timestamp(const std::vector<int64_t> & val) {
    timestamp = val;
  }

  bool operator == (const KeyValueStore_KVEval_args & rhs) const
  {
    if (!(counter_key == rhs.counter_key))
      return false;
    if (!(user_post == rhs.user_post))
      return false;
    if (!(user_list == rhs.user_list))
      return false;
    if (!(clientid == rhs.clientid))
      return false;
    if (!(timestamp == rhs.timestamp))
      return false;
    return true;
  }
  bool operator != (const KeyValueStore_KVEval_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const KeyValueStore_KVEval_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class KeyValueStore_KVEval_pargs {
 public:


  virtual ~KeyValueStore_KVEval_pargs() throw() {}

  const std::string* counter_key;
  const std::string* user_post;
  const std::string* user_list;
  const std::string* clientid;
  const std::vector<int64_t> * timestamp;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

class KeyValueStoreClient : virtual public KeyValueStoreIf {
 public:
  KeyValueStoreClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  KeyValueStoreClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void Get(GetResponse& _return, const std::string& key);
  void send_Get(const std::string& key);
  void recv_Get(GetResponse& _return);
  void GetList(GetListResponse& _return, const std::string& key);
  void send_GetList(const std::string& key);
  void recv_GetList(GetListResponse& _return);
  KVStoreStatus::type Put(const std::string& key, const std::string& value, const std::string& clientid);
  void send_Put(const std::string& key, const std::string& value, const std::string& clientid);
  KVStoreStatus::type recv_Put();
  KVStoreStatus::type AddToList(const std::string& key, const std::string& value, const std::string& clientid);
  void send_AddToList(const std::string& key, const std::string& value, const std::string& clientid);
  KVStoreStatus::type recv_AddToList();
  KVStoreStatus::type RemoveFromList(const std::string& key, const std::string& value, const std::string& clientid);
  void send_RemoveFromList(const std::string& key, const std::string& value, const std::string& clientid);
  KVStoreStatus::type recv_RemoveFromList();
  KVStoreStatus::type Eval(const std::string& counter_key, const std::string& user_post, const std::string& user_list, const std::string& clientid);
  void send_Eval(const std::string& counter_key, const std::string& user_post, const std::string& user_list, const std::string& clientid);
  KVStoreStatus::type recv_Eval();
  void KVPut(const std::string& key, const std::string& value, const std::string& clientid);
  void send_KVPut(const std::string& key, const std::string& value, const std::string& clientid);
  void KVAddToList(const std::string& key, const std::string& value, const std::string& clientid);
  void send_KVAddToList(const std::string& key, const std::string& value, const std::string& clientid);
  void KVRemoveFromList(const std::string& key, const std::string& value, const std::string& clientid);
  void send_KVRemoveFromList(const std::string& key, const std::string& value, const std::string& clientid);
  void KVEval(const std::string& counter_key, const std::string& user_post, const std::string& user_list, const std::string& clientid, const std::vector<int64_t> & timestamp);
  void send_KVEval(const std::string& counter_key, const std::string& user_post, const std::string& user_list, const std::string& clientid, const std::vector<int64_t> & timestamp);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class KeyValueStoreProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<KeyValueStoreIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (KeyValueStoreProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_Get(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_GetList(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_Put(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_AddToList(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_RemoveFromList(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_Eval(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_KVPut(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_KVAddToList(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_KVRemoveFromList(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_KVEval(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  KeyValueStoreProcessor(boost::shared_ptr<KeyValueStoreIf> iface) :
    iface_(iface) {
    processMap_["Get"] = &KeyValueStoreProcessor::process_Get;
    processMap_["GetList"] = &KeyValueStoreProcessor::process_GetList;
    processMap_["Put"] = &KeyValueStoreProcessor::process_Put;
    processMap_["AddToList"] = &KeyValueStoreProcessor::process_AddToList;
    processMap_["RemoveFromList"] = &KeyValueStoreProcessor::process_RemoveFromList;
    processMap_["Eval"] = &KeyValueStoreProcessor::process_Eval;
    processMap_["KVPut"] = &KeyValueStoreProcessor::process_KVPut;
    processMap_["KVAddToList"] = &KeyValueStoreProcessor::process_KVAddToList;
    processMap_["KVRemoveFromList"] = &KeyValueStoreProcessor::process_KVRemoveFromList;
    processMap_["KVEval"] = &KeyValueStoreProcessor::process_KVEval;
  }

  virtual ~KeyValueStoreProcessor() {}
};

class KeyValueStoreProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  KeyValueStoreProcessorFactory(const ::boost::shared_ptr< KeyValueStoreIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< KeyValueStoreIfFactory > handlerFactory_;
};

class KeyValueStoreMultiface : virtual public KeyValueStoreIf {
 public:
  KeyValueStoreMultiface(std::vector<boost::shared_ptr<KeyValueStoreIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~KeyValueStoreMultiface() {}
 protected:
  std::vector<boost::shared_ptr<KeyValueStoreIf> > ifaces_;
  KeyValueStoreMultiface() {}
  void add(boost::shared_ptr<KeyValueStoreIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void Get(GetResponse& _return, const std::string& key) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Get(_return, key);
    }
    ifaces_[i]->Get(_return, key);
    return;
  }

  void GetList(GetListResponse& _return, const std::string& key) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->GetList(_return, key);
    }
    ifaces_[i]->GetList(_return, key);
    return;
  }

  KVStoreStatus::type Put(const std::string& key, const std::string& value, const std::string& clientid) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Put(key, value, clientid);
    }
    return ifaces_[i]->Put(key, value, clientid);
  }

  KVStoreStatus::type AddToList(const std::string& key, const std::string& value, const std::string& clientid) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->AddToList(key, value, clientid);
    }
    return ifaces_[i]->AddToList(key, value, clientid);
  }

  KVStoreStatus::type RemoveFromList(const std::string& key, const std::string& value, const std::string& clientid) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->RemoveFromList(key, value, clientid);
    }
    return ifaces_[i]->RemoveFromList(key, value, clientid);
  }

  KVStoreStatus::type Eval(const std::string& counter_key, const std::string& user_post, const std::string& user_list, const std::string& clientid) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->Eval(counter_key, user_post, user_list, clientid);
    }
    return ifaces_[i]->Eval(counter_key, user_post, user_list, clientid);
  }

  void KVPut(const std::string& key, const std::string& value, const std::string& clientid) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->KVPut(key, value, clientid);
    }
    ifaces_[i]->KVPut(key, value, clientid);
  }

  void KVAddToList(const std::string& key, const std::string& value, const std::string& clientid) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->KVAddToList(key, value, clientid);
    }
    ifaces_[i]->KVAddToList(key, value, clientid);
  }

  void KVRemoveFromList(const std::string& key, const std::string& value, const std::string& clientid) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->KVRemoveFromList(key, value, clientid);
    }
    ifaces_[i]->KVRemoveFromList(key, value, clientid);
  }

  void KVEval(const std::string& counter_key, const std::string& user_post, const std::string& user_list, const std::string& clientid, const std::vector<int64_t> & timestamp) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->KVEval(counter_key, user_post, user_list, clientid, timestamp);
    }
    ifaces_[i]->KVEval(counter_key, user_post, user_list, clientid, timestamp);
  }

};

} // namespace

#endif
