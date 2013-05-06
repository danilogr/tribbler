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
typedef std::list<std::string> ListHolder;
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

      kvs::KVStoreStatus::type Eval(const std::string& counter_key, const std::string& user_post, const std::string& user_list, const std::string& clientid);

      /* One-way functions used to implement replication  */
      void KVEval(const std::string& counter_key, const std::string& user_post, const std::string& user_list, const std::string &clientid,  const std::vector<int64_t> & timestamp);

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

      /* This class holds a operation with its timestamp*/
      class BufferedOperation
      {
        public:
          class Operation
          {
            public:
              Operation(const std::string &a1, const std::string &a2,
                        const std::string &a3): arg1(a1), arg2(a2),
                        arg3(a3) {};
              Operation() {};
              std::string arg1,arg2,arg3;
          };

          class Timestamp
          {
            public:
              Timestamp(const std::vector<int64_t> &v, int client) : vt(v), id(client) {};
              Timestamp() {};

              std::vector<int64_t> vt;
              int id;
          };

          Operation op;
          Timestamp ts;

         BufferedOperation(const Timestamp &t, const Operation&o) : op(o), ts(t) {};
         BufferedOperation() {};
      };

      /* This class holds a buffer of timestamp and deals with
       * removing only the ones that are valid.
       * For this adhoc implementation I use a O(n^2) algorithm
       * I think that a linear algorithm is possile (using a
       * priority queue)
       * (Changing is really easy, it's just a matter of recoding
       * getNextOperation())
       * */
      class TimestampBuffer
      {
        private:
          //holds a vector timestamp plus the server that issued it
          std::list<BufferedOperation> buffer;
          std::vector<int64_t> &localts;
          int maxcompare;

        public:
          TimestampBuffer(std::vector<int64_t> &t) : localts(t){ maxcompare = t.size();};

          //gives the next operation to the user or returns false
          //when no more valid operations are available
          //it updates local timestamp
          std::pair<bool,BufferedOperation> getNextOperation()
          {
            if(buffer.size() == 0)
              return std::make_pair(false,BufferedOperation());

            std::list<BufferedOperation>::iterator it = buffer.begin();

            //for each element, check if the element a valid next timestamp

            bool found = false;

            //look for a candidate
            while(it != buffer.end() && !found)
            {

                BufferedOperation &bo = *it;
                BufferedOperation::Timestamp &ts= bo.ts;
                found = true;


                for(unsigned int i=0; i <  ts.vt.size(); i++)
                {
                  //checking the guy that sent
                  if(i == ts.id)
                  {
                    //check condition
                    if(localts[i] != ts.vt[i] -1)
                    {
                      found = false;
                      break;
                    }
                  } else {
                    //check condition
                    if(localts[i] < ts.vt[i])
                    {
                      found = false;
                      break;
                    }

                  }
                }
                //just increment if nothing was found
                if(!found)
                  it++;
            }

            //if found
            if(found)
            {

              BufferedOperation bo = *it;
              BufferedOperation::Timestamp &ts = bo.ts;
              //adjust local clock



              //increment local (copy local)
              localts[ts.id] = ts.vt[ts.id];

              //remove from buffer
              buffer.erase(it);

              //return
              return std::make_pair(true,bo);
            } else {
              return std::make_pair(false,BufferedOperation());
            }


          }

          void bufferize(const std::vector<int64_t> &ts, int id, const std::string &arg1, const std::string &arg2, const std::string &arg3)
          {
              buffer.push_back(BufferedOperation(BufferedOperation::Timestamp(ts,id),BufferedOperation::Operation(arg1,arg2,arg3)));
          }
      };

      TimestampBuffer buf;

      /* Remote functions used to update other servers */
      void RemoteEval(std::string arg1, std::string arg2, std::string arg3);
      void RemotePut(std::string key, std::string value);
      void RemoteAddToList(std::string key, std::string value);
      void RemoteRemoveFromList(std::string key, std::string value);

      /* Eval function */
      bool evaluate(const std::string &global, const std::string &post, const std::string &list);

};


#endif
