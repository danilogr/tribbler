#ifndef TRIBBLESERVER_H
#define TRIBBLESERVER_H


#include "Tribbler.h"
#include "KeyValueStore.h"

namespace at = ::apache::thrift;
namespace att = ::apache::thrift::transport;
namespace ats = ::apache::thrift::server;
namespace atp = ::apache::thrift::protocol;

namespace kvs = ::KeyValueStore;



class TribblerHandler : virtual public Tribbler::TribblerIf {
 public:

  TribblerHandler(std::string storageServer, int storageServerPort);

  Tribbler::TribbleStatus::type CreateUser(const std::string& userid); 

  Tribbler::TribbleStatus::type AddSubscription(const std::string& userid, const std::string& subscribeto);

  Tribbler::TribbleStatus::type RemoveSubscription(const std::string& userid, const std::string& subscribeto);

  Tribbler::TribbleStatus::type PostTribble(const std::string& userid, const std::string& tribbleContents);

  void GetTribbles(Tribbler::TribbleResponse& _return, const std::string& userid);

  void GetTribblesBySubscription(Tribbler::TribbleResponse& _return, const std::string& userid);
  
  void GetSubscriptions(Tribbler::SubscriptionResponse& _return, const std::string& userid);



  // Functions from interacting with the storage RPC server
  kvs::KVStoreStatus::type AddToList(std::string key, std::string value);

  kvs::KVStoreStatus::type RemoveFromList(std::string key, std::string value);

  kvs::KVStoreStatus::type Put(std::string key, std::string value);

  kvs::GetResponse Get(std::string key);

  kvs::GetListResponse GetList(std::string key);

 private:
  std::string _storageServer;
  int _storageServerPort;


  //check if user exists 
  bool keyExists(std::string username);

  //function that transforms a list of tribbles_id into a list of tribbles
  void readAndFill(const std::vector<int64_t> &input,
                        std::vector<Tribbler::Tribble> &output);

  //function that converts a vector<string> to vector<int64_t>
  void vstringToVint64(const std::vector<std::string> &input, std::vector<int64_t> &list);

  //functions used for marshalling
  void decode(const std::string &input,
           Tribbler::Tribble &output);

  std::string encode(const Tribbler::Tribble &input);



  /* Returns a timestamp (unique) to be used
   * for assigning unique ids to tribbles
   * */
  std::string  getTimestamp();

};




#endif
