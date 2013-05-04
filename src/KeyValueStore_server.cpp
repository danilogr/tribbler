#include <boost/lexical_cast.hpp>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <new>

#include "KeyValueStore_server.h"

using boost::shared_ptr;

//using namespace  ::KeyValueStore;
//KeyValueStoreHandler::
KeyValueStoreHandler::KeyValueStoreHandler(int argc, char** argv) {
  // Your initialization goes here
  _id = boost::lexical_cast<int>(argv[1]);
  int index = 0;

  for(int i = 3; i+1 < argc; i += 2) {
    if (index == _id) {
      _backendServerVector.push_back(std::make_pair("localhost", boost::lexical_cast<int>(argv[2])));
    }
    std::string peer_ip(argv[i]);
    int peer_port = atoi(argv[i+1]);
    _backendServerVector.push_back(std::make_pair(peer_ip, peer_port));
    std::cout << "Backend server at: " << peer_ip << " on port: " << peer_port << std::endl;
  }
}

// single_keys btree_map<string,string>
// list_keys btree_map<string, btree_set<string>>

// ========================================================================================================
void KeyValueStoreHandler::Get(kvs::GetResponse& _return, const std::string& key) {
  kvs::KVStoreStatus::type response = kvs::KVStoreStatus::OK;

  //try to find key
  KeyMap::iterator i = single_keys.find(key);
  if(i == single_keys.end())
  {
    std::cout << "GET" << key << " FROM" << "%{EKEYNOTFOUND}" <<std::endl;
    response = kvs::KVStoreStatus::EKEYNOTFOUND;
  } else {
    //key found, get it
    _return.value = (*i).second;
    std::cout << "GET" << key << " FROM" <<std::endl;
  }

  _return.status =  response;
}

// ========================================================================================================
void KeyValueStoreHandler::GetList(kvs::GetListResponse& _return, const std::string& key) {

  kvs::KVStoreStatus::type response = kvs::KVStoreStatus::OK;

  //try to find key
  ListMap::iterator i = list_keys.find(key);
  if(i == list_keys.end())
  {
    std::cout << "GETLIST" << key << " FROM" << "{EKEYNOTFOUND}" <<std::endl;
    response = kvs::KVStoreStatus::EKEYNOTFOUND;
    _return.values.clear();
  } else {
    //key found, get it
    std::vector<std::string>  ans;
    ListHolder &listval = (*i).second;

    //fill vector
    _return.values.clear();
    _return.values.reserve(listval.size());
    ListHolder::iterator b, e = listval.end();
    for(b = listval.begin(); b != e; b++)
      _return.values.push_back(*b);

    std::cout << "GETLIST" << key << " FROM" <<std::endl;
  }

  _return.status = response; 
}

// ========================================================================================================
kvs::KVStoreStatus::type KeyValueStoreHandler::Put(const std::string& key, const std::string& value, const std::string& clientid) {
  kvs::KVStoreStatus::type response = kvs::KVStoreStatus::OK;

  try
  {
    single_keys[key] = value;
    std::cout << "PUT" << key << " = " << value << " FROM" <<  clientid << std::endl;
  } catch (std::bad_alloc& ba)
  {
    std::cout << "PUT" << key << " = " << value << " FROM" <<  clientid << " [FAILED]" << std::endl;
    response = kvs::KVStoreStatus::EPUTFAILED;
  }


  //TODO
  return response;
}

// ========================================================================================================
kvs::KVStoreStatus::type KeyValueStoreHandler::AddToList(const std::string& key, const std::string& value, const std::string& clientid) {
  kvs::KVStoreStatus::type response = kvs::KVStoreStatus::OK;


  try
  {
    ListHolder &listval = list_keys[key];
    std::pair<ListHolder::iterator,bool> ret = listval.insert(value);

    std::cout << "AddToList" << key << " = " << value << " FROM" <<  clientid;
    //if data already exists
    if(ret.second == false)
    {
      response = kvs::KVStoreStatus::EITEMEXISTS;
      std::cout << "{EITEMEXISTS}";
    }
    std::cout << std::endl;
  } catch (std::bad_alloc& ba)
  {
    std::cout << "AddToList" << key << " = " << value << " FROM" <<  clientid << " [FAILED]" << std::endl;
    response = kvs::KVStoreStatus::EPUTFAILED;
  }

  //TODO

  return response; 
}

// ========================================================================================================

kvs::KVStoreStatus::type KeyValueStoreHandler::RemoveFromList(const std::string& key, const std::string& value, const std::string& clientid) {
  kvs::KVStoreStatus::type response = kvs::KVStoreStatus::OK;

  //look for item
  //never return a key not found as a empty will be created
  ListMap::iterator i = list_keys.find(key);
  if(i == list_keys.end())
  {

    std::cout << "RemoveFromList" << key << " = " << value << " FROM" <<  clientid <<"{EKEYNOTFOUND}"<< std::endl;

  } else {
    //list found
    ListHolder &listval = (*i).second;

    //search the element
    ListHolder::iterator ret = listval.find(value);

    std::cout << "RemoveFromList" << key << " = " << value << " FROM" <<  clientid;

    //item not found
    if( ret == listval.end())
    {
      std::cout << "{EITEMNOTFOUND}";
      response = kvs::KVStoreStatus::EITEMNOTFOUND;
    } else {
      //item found
      single_keys.erase(*ret); 
    }

  }

  std::cout << std::endl;

  //TODO


  return response; 
}


// ========================================================================================================
int main(int argc, char **argv) {
  if((argc < 3) || !(argc % 2)) {
    std::cerr << "Usage: " << argv[0] << " id localport peer1 port1..." << std::endl;
    exit(1);
  }
  int port = boost::lexical_cast<int>(argv[2]);
  shared_ptr<KeyValueStoreHandler> handler(new KeyValueStoreHandler(argc, argv));
  shared_ptr<at::TProcessor> processor(new kvs::KeyValueStoreProcessor(handler));
  shared_ptr<ats::TServerTransport> serverTransport(new att::TServerSocket(port));
  shared_ptr<att::TTransportFactory> transportFactory(new att::TBufferedTransportFactory());
  shared_ptr<atp::TProtocolFactory> protocolFactory(new atp::TBinaryProtocolFactory());

  std::cout << "Starting KV Server" << std::endl;

  ats::TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

