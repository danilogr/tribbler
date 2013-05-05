#include <boost/lexical_cast.hpp>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <new>
#include <transport/TSocket.h>


#include "KeyValueStore_server.h"

using boost::shared_ptr;

//using namespace  ::KeyValueStore;
//KeyValueStoreHandler::
KeyValueStoreHandler::KeyValueStoreHandler(int instanceId, const ServerList &server) {

    //server id
    _id = instanceId;
    _idstr = boost::lexical_cast<std::string>(_id);

    //copy server list
    _backendServerVector = server;


    //prepare timestamp
    _timestamp.resize(server.size()+1);
    std::fill(_timestamp.begin(),_timestamp.end(), 0);

    //fill vectors
    _backendDead.resize(server.size());
    _backendOnce.resize(server.size());
    std::fill(_backendDead.begin(), _backendDead.end(), false);
    std::fill(_backendOnce.begin(), _backendOnce.end(), false);

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


      //check if this was not a local call
      if(clientid != _idstr)
      {
        RemotePut(key,value);
      }



    } catch (std::bad_alloc& ba)
    {
      std::cout << "PUT" << key << " = " << value << " FROM" <<  clientid << " [FAILED]" << std::endl;
      response = kvs::KVStoreStatus::EPUTFAILED;
    }


    return response;
}

// ========================================================================================================
kvs::KVStoreStatus::type KeyValueStoreHandler::AddToList(const std::string& key, const std::string& value, const std::string& clientid) {
  kvs::KVStoreStatus::type response = kvs::KVStoreStatus::OK;


  try
  {
    ListHolder &listval = list_keys[key];
    ListHolder::iterator it = std::find(listval.begin(),listval.end(),value);

    std::cout << "AddToList" << key << " = " << value << " FROM" <<  clientid;
    //if data already exists
    if(it != listval.end())
    {
      response = kvs::KVStoreStatus::EITEMEXISTS;
      std::cout << "{EITEMEXISTS}";
    } else { 
      //new data add ==> propagate
      listval.push_front(value);
      //check if this was not a local call
      if(clientid != _idstr)
      {
        RemoteAddToList(key,value);
      }

    }
    std::cout << std::endl;
  } catch (std::bad_alloc& ba)
  {
    std::cout << "AddToList" << key << " = " << value << " FROM" <<  clientid << " [FAILED]" << std::endl;
    response = kvs::KVStoreStatus::EPUTFAILED;
  }


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
    ListHolder::iterator ret = std::find(listval.begin(),listval.end(),value);

    std::cout << "RemoveFromList" << key << " = " << value << " FROM" <<  clientid;

    //item not found
    if( ret == listval.end())
    {
      std::cout << "{EITEMNOTFOUND}";
      response = kvs::KVStoreStatus::EITEMNOTFOUND;
    } else {
      //item found
      listval.erase(ret); 


      //check if this was not a local call
      if(clientid != _idstr)
      {
        RemoteRemoveFromList(key,value);
      }

    }

  }

  std::cout << std::endl;



  return response; 
}

kvs::KVStoreStatus::type KeyValueStoreHandler::Eval(const std::string& counter_key, const std::string& user_post, const std::string& user_list, const std::string& clientid)
{

    kvs::KVStoreStatus::type response = kvs::KVStoreStatus::OK;

    std::cout << "EVAL [" << counter_key << "," << user_post << "," << user_list << "] FROM" <<  clientid << std::endl;


    //if evaluate succeds
    if(evaluate(counter_key,user_post,user_list))
    {

      //check if this was not a local call
      //and propagate
      if(clientid != _idstr)
      {
        RemoteEval(counter_key,user_post,user_list);
      }

    } else {

      response = kvs::KVStoreStatus::EVALFAILED;
    }

    return response;


}


/*
 * Special evaluate function
 * TODO: change to evaluate a simple script language
 * */
bool KeyValueStoreHandler::evaluate(const std::string &global, const std::string &post, const std::string &list)
{

  try
  {

    //
    //first, increment global counter "global"
    //
    std::string global_counter =  single_keys[global];
    int counter = 0;

    try {
      counter = boost::lexical_cast<int>( global_counter );
    } catch( boost::bad_lexical_cast const& ) {
      //initialize with 0
      global_counter = "0";
    }
    //increment
    counter++;

    //save 
    single_keys[global] = boost::lexical_cast<std::string>(counter);

    //
    //second, save user post
    //
    single_keys[global_counter] = post;

    //
    //third, add post to user list
    //
    //remove smallest element if list is bigger than 100

    //a) test list size
    ListHolder &l = list_keys[list];
    if(l.size() == 100)
    {
      l.pop_back();
    }
    //b) add new element
    l.push_front(global_counter);



  } catch (std::bad_alloc& ba)
  {
    return false;
  }

  return true;

}


/*
 * One-way functions used for replication
 * (functions that were receieved from other server as a way to replicate data here)
 * */
void  KeyValueStoreHandler::KVEval(const std::string& counter_key, const std::string& user_post, const std::string& user_list, const std::string& clientid, const std::vector<int64_t> & timestamp)
{
  //TODO(danilo)
  //Deal with timestamp and clientid(implement queue)
  
  //replicate call
  evaluate(counter_key,user_post,user_list);

}

void KeyValueStoreHandler::KVPut(const std::string& key, const std::string& value, const std::string& clientid) {

  Put(key,value,_idstr);

}

void KeyValueStoreHandler::KVAddToList(const std::string& key, const std::string& value, const std::string& clientid) {

  AddToList(key,value,_idstr);
}

void KeyValueStoreHandler::KVRemoveFromList(const std::string& key, const std::string& value, const std::string& clientid) {
  RemoveFromList(key,value,_idstr);

}


/*
 * Function call to the other servers
 * */



void KeyValueStoreHandler::RemotePut(std::string key, std::string value)
{
  // Making the RPC Call to each Storage server in a list
  int c = _backendServerVector.size();
  for(int i = 0; i < c; i++)
  {
    //if server is not dead
    if(!_backendDead[i])
    {

      boost::shared_ptr<att::TSocket> socket(new att::TSocket(_backendServerVector[i].first,_backendServerVector[i].second));
      boost::shared_ptr<att::TTransport> transport(new att::TBufferedTransport(socket));
      boost::shared_ptr<atp::TProtocol> protocol(new atp::TBinaryProtocol(transport));
      kvs::KeyValueStoreClient client(protocol);
      try
      {
        transport->open();
        client.KVPut(key, value, _idstr);
        transport->close();
        //all ok, so it was on
        _backendOnce[i] = true;
      } catch (at::TException &tx)
      {
        //error sending to this server

        //was it ever on?
        if(_backendOnce[i])
        {
          //therefore I consider this guy to be dead
          _backendDead[i] = true;
        }
        //if it was never on, maybe it will join us latter
      }
    }
  }
}



void  KeyValueStoreHandler::RemoteAddToList(std::string key, std::string value)
{
  // Making the RPC Call to each Storage server in a list
  int c = _backendServerVector.size();
  for(int i = 0; i < c; i++)
  {
    //if server is not dead
    if(!_backendDead[i])
    {

      boost::shared_ptr<att::TSocket> socket(new att::TSocket(_backendServerVector[i].first,_backendServerVector[i].second));
      boost::shared_ptr<att::TTransport> transport(new att::TBufferedTransport(socket));
      boost::shared_ptr<atp::TProtocol> protocol(new atp::TBinaryProtocol(transport));
      kvs::KeyValueStoreClient client(protocol);
      try
      {
        transport->open();
        client.KVAddToList(key, value, _idstr);
        transport->close();
        //all ok, so it was on
        _backendOnce[i] = true;
      } catch (at::TException &tx)
      {
        //error sending to this server

        //was it ever on?
        if(_backendOnce[i])
        {
          //therefore I consider this guy to be dead
          _backendDead[i] = true;
        }
        //if it was never on, maybe it will join us latter
      }
    }
  }

}

void  KeyValueStoreHandler::RemoteRemoveFromList(std::string key, std::string value)
{

  // Making the RPC Call to each Storage server in a list
  int c = _backendServerVector.size();
  for(int i = 0; i < c; i++)
  {
    //if server is not dead
    if(!_backendDead[i])
    {

      boost::shared_ptr<att::TSocket> socket(new att::TSocket(_backendServerVector[i].first,_backendServerVector[i].second));
      boost::shared_ptr<att::TTransport> transport(new att::TBufferedTransport(socket));
      boost::shared_ptr<atp::TProtocol> protocol(new atp::TBinaryProtocol(transport));
      kvs::KeyValueStoreClient client(protocol);
      try
      {
        transport->open();
        client.KVRemoveFromList(key, value, _idstr );
        transport->close();
        //all ok, so it was on
        _backendOnce[i] = true;
      } catch (at::TException &tx)
      {
        //error sending to this server

        //was it ever on?
        if(_backendOnce[i])
        {
          //therefore I consider this guy to be dead
          _backendDead[i] = true;
        }
        //if it was never on, maybe it will join us latter
      }
    }
  }

}


void KeyValueStoreHandler::RemoteEval(std::string arg1, std::string arg2, std::string arg3)
{
  // increment local timestamp
  _timestamp[_id]++;

  // Making the RPC Call to each Storage server in a list
  int c = _backendServerVector.size();
  for(int i = 0; i < c; i++)
  {
    //if server is not dead
    if(!_backendDead[i])
    {

      boost::shared_ptr<att::TSocket> socket(new att::TSocket(_backendServerVector[i].first,_backendServerVector[i].second));
      boost::shared_ptr<att::TTransport> transport(new att::TBufferedTransport(socket));
      boost::shared_ptr<atp::TProtocol> protocol(new atp::TBinaryProtocol(transport));
      kvs::KeyValueStoreClient client(protocol);
      try
      {
        transport->open();
        client.KVEval(arg1, arg2, arg3, _idstr,_timestamp);
        transport->close();
        //all ok, so it was on
        _backendOnce[i] = true;
      } catch (at::TException &tx)
      {
        //error sending to this server

        //was it ever on?
        if(_backendOnce[i])
        {
          //therefore I consider this guy to be dead
          _backendDead[i] = true;
        }
        //if it was never on, maybe it will join us latter
      }
    }
  }
}


// ========================================================================================================
int main(int argc, char **argv) {
  if((argc < 3) || !(argc % 2)) {
    std::cerr << "Usage: " << argv[0] << " id localport peer1 port1..." << std::endl;
    exit(1);
  }

  //server port
  int port = boost::lexical_cast<int>(argv[2]);

  ServerList tmp;

  //parse server ids
  //(we are guaranted that argc % 2
  for (int i = 3; i < argc; i+=2)
  {
    tmp.push_back(std::make_pair(argv[i], boost::lexical_cast<int>(argv[i+1])));
    std::cout << "Server " << argv[i] << ":" << argv[i+1] << std::endl;
  } 


  shared_ptr<KeyValueStoreHandler> handler(new KeyValueStoreHandler(boost::lexical_cast<int>(argv[1]), tmp));
  shared_ptr<at::TProcessor> processor(new kvs::KeyValueStoreProcessor(handler));
  shared_ptr<ats::TServerTransport> serverTransport(new att::TServerSocket(port));
  shared_ptr<att::TTransportFactory> transportFactory(new att::TBufferedTransportFactory());
  shared_ptr<atp::TProtocolFactory> protocolFactory(new atp::TBinaryProtocolFactory());

  std::cout << "Starting KV Server" << std::endl;

  ats::TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

