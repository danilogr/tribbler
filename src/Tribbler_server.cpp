#include <errno.h>
#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>
#include <sstream>
#include <stdio.h>


#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm.hpp>
#include <boost/algorithm/string.hpp>
#include <transport/TSocket.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

#include "Tribbler_server.h"

using boost::shared_ptr;

TribblerHandler::TribblerHandler(std::string storageServer, int storageServerPort)
{
  // Your initialization goes here
  _storageServer = storageServer;
  _storageServerPort = storageServerPort;

  //
}


Tribbler::TribbleStatus::type TribblerHandler::CreateUser(const std::string& userid)
{

  //check user for illegal/unwanted characters (not a requirement) TODO
  //check user existance  
  kvs::KVStoreStatus::type kvstatus;
  Tribbler::TribbleStatus::type response;
  //key not found (user does not exist)
  if(!keyExists(userid +"_n"))
  {
    kvstatus = Put(userid + "_n","t");
    if(kvstatus == kvs::KVStoreStatus::OK)
    {
      response =  Tribbler::TribbleStatus::OK;
    } else {
      response = Tribbler::TribbleStatus::STORE_FAILED;
    }
  } else {
    response =  Tribbler::TribbleStatus::EEXISTS; 
  }

  return response;
}


Tribbler::TribbleStatus::type TribblerHandler::AddSubscription(const std::string& userid, const std::string& subscribeto)
{
  Tribbler::TribbleStatus::type response;
  std::string _userid(userid);
  std::string _subscribeto(subscribeto);
  _userid += "_n";
  _subscribeto += "_n";

  //check user exists
  if(keyExists(_userid))
  {
    //check subscribe to user existance
    if(userid != subscribeto && keyExists(_subscribeto))
    {
      //update subscribing list
      kvs::KVStoreStatus::type rsp = AddToList(userid+"_l",subscribeto);
      switch ((int)rsp)
      {
        case (int)kvs::KVStoreStatus::EITEMEXISTS:
          response = Tribbler::TribbleStatus::EEXISTS;
          break;

        case (int)kvs::KVStoreStatus::OK:
          {
            //case it was ok we should update the inverse pointer list
            //(this can be really useffull in real world cases (e.g. twitter)
            //when user wants a list of which users follow her
            //in other hand we pay by doubling our storage
            //bool stored =false;
            //while(!stored)
            //{
            //  if(kvs::KVStoreStatus::EPUTFAILED != AddToList(subscribeto+"_i",userid))
            //    stored = true;

            //}

            response = Tribbler::TribbleStatus::OK;
          }
          break;

        case (int)kvs::KVStoreStatus::EPUTFAILED:
          response = Tribbler::TribbleStatus::STORE_FAILED;
          break;
      }
    } else {
      response = Tribbler::TribbleStatus::INVALID_SUBSCRIBETO;
    }
  } else {
    response = Tribbler::TribbleStatus::INVALID_USER;
  }

  return response;
}


Tribbler::TribbleStatus::type TribblerHandler::RemoveSubscription(const std::string& userid, const std::string& subscribeto)
{

  Tribbler::TribbleStatus::type response;
  std::string _userid(userid);
  std::string _subscribeto(subscribeto);
  _userid += "_n";
  _subscribeto += "_n";
  //check user exists
  if(keyExists(_userid))
  {
    //check subscribe to user existance
    if(keyExists(_subscribeto))
    {
      //update subscribing list
      kvs::KVStoreStatus::type rsp = RemoveFromList(userid+"_l",subscribeto);
      switch ((int)rsp)
      {
        case (int)kvs::KVStoreStatus::EITEMNOTFOUND:
          response = Tribbler::TribbleStatus::INVALID_SUBSCRIBETO;
          break;

        case (int)kvs::KVStoreStatus::OK:
          response = Tribbler::TribbleStatus::OK;

          //case it was ok we should update the inverse pointer list
          //(this can be really useffull in real world cases (e.g. twitter)
          //when user wants a list of which users follow her
          //in other hand we pay by doubling our storage
          //kvs::KVStoreStatus::type nrsp = RemoveFromList(subscribeto+"_i",userid);
          //if it is not found its ok
          //but maybe we should log warnings about that

          break;
      }
    }
  } else {
    response = Tribbler::TribbleStatus::INVALID_USER;
  }
  return response;
}

Tribbler::TribbleStatus::type TribblerHandler::PostTribble(const std::string& userid, const std::string& tribbleContents)
{
  std::string _userid(userid);
  _userid += "_n";

  //avoid empty strings
  std::string post(tribbleContents);
  boost::trim(post);
  if(post.size() == 0)
    return Tribbler::TribbleStatus::STORE_FAILED;

  //OK by default
  Tribbler::TribbleStatus::type response = Tribbler::TribbleStatus::OK;

  //check user exists
  if(keyExists(_userid))
  {
    //retrieve subscribing list
    kvs::GetListResponse rsp = GetList(userid+"_p");

    //if no item was found that means that user never tribbled
    //if a item was found then just copy
    bool itemToRemoveFlag = false;
    std::string itemToRemove;
    if (rsp.status == kvs::KVStoreStatus::OK)
    {
      if(rsp.values.size() > 99)
      {
        //convert to int
        std::vector<int64_t> list;
        vstringToVint64(rsp.values,list);

        //sort vector
        std::sort(list.begin(),list.end(), std::greater<int64_t>());


        int s = rsp.values.size();
        //if for some error reason this is bigger than 100
        while (s > 100)
        {
          //remove until we have exactly 100
          RemoveFromList(userid+"_p",boost::lexical_cast<std::string>(list.back()));
          list.pop_back();
          s--;
        }

        //mark that we should remove
        itemToRemove = boost::lexical_cast<std::string>(list.back());
        itemToRemoveFlag = true;


        //this could be saved somewhere else
        //e.g. key userid+"_op" where ol stands for old posts
      }
    } //else { //only EKEYNOTFOUND fits
    //posts lists not found (dont need to worry about adding one more)
    //}

    //insert the new tribble
    Tribbler::Tribble tmp;
    tmp.userid = userid;

    tmp.contents = post;


    //marshaling
    std::string encodedpost = encode(tmp);

    //try to create post
    //SYNC BEGIN
    std::string tmptime = getTimestamp();
    kvs::KVStoreStatus::type ans = Put(tmptime,encodedpost);

    //ok inserting
    if(kvs::KVStoreStatus::OK == ans)
    {
      //update user list
      AddToList(userid+"_p",tmptime);

      //remove oldest element 
      if(itemToRemoveFlag)
        RemoveFromList(userid+"_p",itemToRemove);
    } else {
      response=Tribbler::TribbleStatus::STORE_FAILED;
    }
    //SYNC END

  } else {
    response= Tribbler::TribbleStatus::INVALID_USER;
  }
  return response;

}

void TribblerHandler::GetTribbles(Tribbler::TribbleResponse& _return, const std::string& userid)
{
  std::string _userid(userid);
  _userid += "_n";
  //check user exists
  if(keyExists(_userid))
  {
    kvs::GetListResponse rsp = GetList(userid+"_p");
    _return.status = Tribbler::TribbleStatus::OK;
    _return.tribbles.empty();
    _return.tribbles.reserve(100);//wait for worst case
    if (rsp.status == kvs::KVStoreStatus::OK)
    {
      //items found, transform to int
      std::vector<int64_t> list;
      vstringToVint64(rsp.values,list);

      //sort vector
      std::sort(list.begin(),list.end(), std::greater<int64_t>());

      //read all tribbles and fill list
      readAndFill(list,_return.tribbles);

      //ready to return ;]
    } else { //only EKEYNOTFOUND fits
      //empty return
    }
  } else {
    _return.status = Tribbler::TribbleStatus::INVALID_USER;
  }

}

void TribblerHandler::GetTribblesBySubscription(Tribbler::TribbleResponse& _return, const std::string& userid)
{
  std::string _userid(userid);
  _userid += "_n";
  //check user exists
  if(keyExists(_userid))
  {
    //retrieve subscribing list
    kvs::GetListResponse usernames = GetList(userid+"_l");
    _return.status = Tribbler::TribbleStatus::OK;
    _return.tribbles.empty();


    std::vector<int64_t> biglist;
    //if user ever had subscriptions
    if (usernames.status == kvs::KVStoreStatus::OK)
    {
      //get size and reserve memory
      if (usernames.values.size() > 0)
      {
        //worst case resizing
        _return.tribbles.reserve(100);
        biglist.reserve(usernames.values.size()*100);

        //iterate each user post list and convert to integer
        std::vector<std::string>::const_iterator beg,end = usernames.values.end();
        for(beg = usernames.values.begin(); beg != end; beg++)
        {
          kvs::GetListResponse posts = GetList(*beg+"_p");
          if(posts.status == kvs::KVStoreStatus::OK)
          {
            //convert inserting into biglist
            vstringToVint64(posts.values,biglist);
          }
        }

        //sort big data
        std::sort(biglist.begin(),biglist.end(), std::greater<int64_t>());

        //read all tribbles and fill list (limited to 100 first)
        readAndFill(biglist,_return.tribbles);
      }

      //ready to return ;]
    } else { //only EKEYNOTFOUND fits
      //empty return
    }
  } else {
    _return.status = Tribbler::TribbleStatus::INVALID_USER;
  }


}

void TribblerHandler::GetSubscriptions(Tribbler::SubscriptionResponse& _return, const std::string& userid)
{
  std::string _userid(userid);
  _userid += "_n";
  //check user exists
  if(keyExists(_userid))
  {
    //retrieve subscribing list
    kvs::GetListResponse rsp = GetList(userid+"_l");
    _return.status = Tribbler::TribbleStatus::OK;

    //if no item was found that means that user never tribbled
    //if a item was found then just copy
    if (rsp.status == kvs::KVStoreStatus::OK)
    {
      _return.subscriptions = rsp.values;
    } else { //only EKEYNOTFOUND fits
      //returns empty vector
      _return.subscriptions.empty();
    }
  } else {
    _return.status = Tribbler::TribbleStatus::INVALID_USER;
  }
}

/*
 * Functions used by exported functions
 *
 */

bool TribblerHandler::keyExists(std::string key)
{
  kvs::GetResponse getr= Get(key);
  bool result = false;
  if(getr.status == kvs::KVStoreStatus::OK)
  {
    result = true;
  } else {
    result = false;
  }
  return result;
}



std::string  TribblerHandler::getTimestamp()
{
  /* This code should be executed in a
   * critical section case we are running
   * our handler multithreaded
   * */
  using boost::lexical_cast;

  std::string response;

  kvs::GetResponse globtime = Get("GLOBAL_TIME");

  //variable found
  if(globtime.status == kvs::KVStoreStatus::OK)
  {
    //increment it
    int newtime = boost::lexical_cast<int>(globtime.value.c_str());
    newtime++;
    response = boost::lexical_cast<std::string>(newtime);
    //save
    bool saved = false;

    //it would be really usefull if kvstore database
    //implements atomic increments
    while(!saved)
    {
      kvs::KVStoreStatus::type rs = Put("GLOBAL_TIME",response);
      if(rs == kvs::KVStoreStatus::OK)
        saved = true;
    }

  } else {


    bool saved = false;

    //it would be really usefull if kvstore database
    //implements atomic increments
    while(!saved)
    {
      kvs::KVStoreStatus::type rs = Put("GLOBAL_TIME","0");
      if(rs == kvs::KVStoreStatus::OK)
        saved = true;
    }

    response = "0";
  }

  return response;
}

//function that transforms a list of tribbles_id into a list of tribbles
//limited to 100 
void TribblerHandler::readAndFill(const std::vector<int64_t> &input,
    std::vector<Tribbler::Tribble> &output)
{
  std::vector<int64_t>::const_iterator beg,end = input.end();
  int counter;
  for(beg = input.begin(), counter = 0; (beg != end) && counter < 100; beg++, counter++)
  {
    //create storage
    Tribbler::Tribble store;
    //store.posted = *beg;

    //make rpc call
    kvs::GetResponse tribble = Get(boost::lexical_cast<std::string>(*beg));

    //that should be the case (otherwise a warning should be issued)
    if(kvs::KVStoreStatus::OK == tribble.status)
    {
      //deserialize
      decode(tribble.value,store);
    } else {
      store.userid = "";
      store.contents = "";
    }

    //save data
    output.push_back(store);

  }

}

//functions used for marshalling
void TribblerHandler::decode(const std::string &input,
    Tribbler::Tribble &output)
{
  unsigned int i=0;
  //states are 0 =user decoding, 1 = dealing with /, 2 = error, 3 = content decoding
  int state = 0;
  std::stringstream user, content;
  for(i = 0; i < input.size(); i++)
  {
    switch(state)
    {
      case 0:
        {
          if(input[i] == '\\')
            state = 1;
          else if(input[i] == ';')
            state = 3;
          else
            user << input[i];
        }
        break;
      case 1:
        {
          state = 0;
          if(input[i] == '\\')
            user << input[i];
          else if(input[i] == ';')
            user << input[i];
          else //error
            state = 2;
        }
        break;
      case 2:
        {
          //error handling
          //warn
        }
        break;
      case 3:
        {
          content << input[i];
        }
        break;
    }
  }

  //saves to output
  output.userid = user.str();
  output.contents = content.str();
}

std::string TribblerHandler::encode(const Tribbler::Tribble &input)
{
  std::stringstream rslt;
  //deal with username
  unsigned int i;

  //deal with first char
  if(input.userid[0] ==';')
    rslt << '\\';

  for(i = 0; i < input.userid.size(); i++)
  {
    rslt << input.userid[i];

    //currently dealing with /
    if(input.userid[i] == '\\')
      rslt << '\\';

    if(i+1 < input.userid.size())
      if(input.userid[i+1] == ';')
      {
        rslt << '\\';
      }

  }

  //add separator
  rslt << ';';

  //deal with twitt
  rslt << input.contents;
  return rslt.str();
}



void TribblerHandler::vstringToVint64(const std::vector<std::string> &input, std::vector<int64_t> &list)
{
  //allocate space if needed
  list.reserve(input.size());

  //transform
  //std::transform(input.begin(),input.end(),list.begin(),boost::lexical_cast<int64_t>);
  std::vector<std::string>::const_iterator beg, end = input.end();
  for(beg = input.begin(); beg!= end; beg++)
    list.push_back(boost::lexical_cast<int64_t>(*beg));
}

/*
 *
 * Functions from interation with the storage RPC server
 *
 **/


kvs::KVStoreStatus::type TribblerHandler::AddToList(std::string key, std::string value)
{
  boost::shared_ptr<att::TSocket> socket(new att::TSocket(_storageServer, _storageServerPort));
  boost::shared_ptr<att::TTransport> transport(new att::TBufferedTransport(socket));
  boost::shared_ptr<atp::TProtocol> protocol(new atp::TBinaryProtocol(transport));
  kvs::KeyValueStoreClient kv_client(protocol);
  // Making the RPC Call
  kvs::KVStoreStatus::type st;
  transport->open();
  st = kv_client.AddToList(key, value,"tribbleserver");
  transport->close();
  return st;
}

kvs::KVStoreStatus::type TribblerHandler::RemoveFromList(std::string key, std::string value)
{
  // Making the RPC Call to the Storage server
  boost::shared_ptr<att::TSocket> socket(new att::TSocket(_storageServer, _storageServerPort));
  boost::shared_ptr<att::TTransport> transport(new att::TBufferedTransport(socket));
  boost::shared_ptr<atp::TProtocol> protocol(new atp::TBinaryProtocol(transport));
  kvs::KeyValueStoreClient client(protocol);
  kvs::KVStoreStatus::type st;
  transport->open();
  st = client.RemoveFromList(key, value,"tribbleserver");
  transport->close();
  return st;
}

kvs::KVStoreStatus::type TribblerHandler::Put(std::string key, std::string value)
{
  // Making the RPC Call to the Storage server
  boost::shared_ptr<att::TSocket> socket(new att::TSocket(_storageServer, _storageServerPort));
  boost::shared_ptr<att::TTransport> transport(new att::TBufferedTransport(socket));
  boost::shared_ptr<atp::TProtocol> protocol(new atp::TBinaryProtocol(transport));
  kvs::KeyValueStoreClient client(protocol);
  kvs::KVStoreStatus::type st;
  transport->open();
  st = client.Put(key, value,"tribbleserver");
  transport->close();
  return st;
}

kvs::GetResponse TribblerHandler::Get(std::string key)
{
  kvs::GetResponse response;
  // Making the RPC Call to the Storage server
  boost::shared_ptr<att::TSocket> socket(new att::TSocket(_storageServer, _storageServerPort));
  boost::shared_ptr<att::TTransport> transport(new att::TBufferedTransport(socket));
  boost::shared_ptr<atp::TProtocol> protocol(new atp::TBinaryProtocol(transport));
  kvs::KeyValueStoreClient client(protocol);
  transport->open();
  client.Get(response, key);
  transport->close();
  return response;
}

kvs::GetListResponse TribblerHandler::GetList(std::string key)
{

  kvs::GetListResponse response;
  // Making the RPC Call to the Storage server
  boost::shared_ptr<att::TSocket> socket(new att::TSocket(_storageServer, _storageServerPort));
  boost::shared_ptr<att::TTransport> transport(new att::TBufferedTransport(socket));
  boost::shared_ptr<atp::TProtocol> protocol(new atp::TBinaryProtocol(transport));

  kvs::KeyValueStoreClient client(protocol);
  transport->open();
  client.GetList(response,key);
  transport->close();

  return response;

}



/* ==================================================================================
 * 
 *                                   Main Function
 *
 * ==================================================================================*/

int main(int argc, char **argv) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <kvServerIP> <kvServerPort> <tribbleServerPort>" << std::endl;
    exit(0);
  }
  std::string storageServer = std::string(argv[1]);
  int storageServerPort = boost::lexical_cast<int>(argv[2]);
  int tribblerPort = boost::lexical_cast<int>(argv[3]);

  shared_ptr<TribblerHandler> handler(new TribblerHandler(storageServer, storageServerPort));
  shared_ptr<at::TProcessor> processor(new Tribbler::TribblerProcessor(handler));
  shared_ptr<ats::TServerTransport> serverTransport(new att::TServerSocket(tribblerPort));
  shared_ptr<att::TTransportFactory> transportFactory(new att::TBufferedTransportFactory());
  shared_ptr<atp::TProtocolFactory> protocolFactory(new atp::TBinaryProtocolFactory());

  std::cout << "Starting Tribbler Server" << std::endl;
  ats::TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
