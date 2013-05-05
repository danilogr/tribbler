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

      /* One-way functions used to implement replication  */

      void KVPut(const std::string& key, const std::string& value, const std::string& clientid, const std::vector<int64_t> & timestamp);

      void KVAddToList(const std::string& key, const std::string& value, const std::string& clientid); 

      void KVRemoveFromList(const std::string& key, const std::string& value, const std::string& clientid); 


  private:
      int _id;
      ServerList _backendServerVector;
      KeyMap single_keys;
      ListMap list_keys;

};


#endif
