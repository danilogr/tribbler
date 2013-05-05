#ifndef KVS_SERVER_H
#define KVS_SERVER_H

#include "KeyValueStore.h"

/* I'm using Google's map implementation using btrees
 * The library is called cpp-btree
 * https://code.google.com/p/cpp-btree/
 * */
#include "btree_map.h"
#include "btree_set.h"

namespace at = ::apache::thrift;
namespace att = ::apache::thrift::transport;
namespace ats = ::apache::thrift::server;
namespace atp = ::apache::thrift::protocol;

namespace kvs = ::KeyValueStore;

typedef btree::btree_map<std::string,std::string> KeyMap;
typedef btree::btree_set<std::string> ListHolder;
typedef btree::btree_map<std::string,ListHolder> ListMap; 
typedef std::pair<std::string, int> Server;
typedef std::vector< Server > ServerList;

class KeyValueStoreHandler : virtual public kvs::KeyValueStoreIf {
  public:
      KeyValueStoreHandler(int instanceId, const ServerList &servers );

      void Get(kvs::GetResponse& _return, const std::string& key);

      void GetList(kvs::GetListResponse& _return, const std::string& key);

      kvs::KVStoreStatus::type Put(const std::string& key, const std::string& value, const std::string& clientid);

      kvs::KVStoreStatus::type AddToList(const std::string& key, const std::string& value, const std::string& clientid);

      kvs::KVStoreStatus::type RemoveFromList(const std::string& key, const std::string& value, const std::string& clientid); 

      kvs::KVStoreStatus::type Eval(const std::string& counter_key, const std::string& user_post, const std::string& user_list);

      /* One-way functions used to implement replication  */
      void KVEval(const std::string& counter_key, const std::string& user_post, const std::string& user_list, const std::vector<int64_t> & timestamp);

      void KVPut(const std::string& key, const std::string& value, const std::string& clientid);

      void KVAddToList(const std::string& key, const std::string& value, const std::string& clientid); 

      void KVRemoveFromList(const std::string& key, const std::string& value, const std::string& clientid); 

  private:
      int _id;
      std::string _idstr;
      ServerList _backendServerVector;
      std::vector<bool> _backendDead;    //if a server is dead or not
      std::vector<bool> _backendOnce;    //if a server was once alive
      std::vector<int64_t> _timestamp;   //local time stamp
      KeyMap single_keys;
      ListMap list_keys;

      /* Remote functions used to update other servers */
      void RemoveEval(std::string arg1, std::string arg2, std::string arg3);
      void RemotePut(std::string key, std::string value);
      void RemoteAddToList(std::string key, std::string value);
      void RemoteRemoveFromList(std::string key, std::string value);

};


#endif
