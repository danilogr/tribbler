// Sample client

#include "Tribbler.h"
#include <transport/TSocket.h>
#include <transport/TBufferTransports.h>
#include <protocol/TBinaryProtocol.h>
#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace Tribbler;
using namespace std;

void printSubscriptions(SubscriptionResponse& sr, string user) {
    unsigned int size = sr.subscriptions.size();
    if (sr.status != TribbleStatus::OK) {
       cout << "GetSubscriptions for user: "<< user << " failed. "
            << "Error code: " << sr.status << endl;
        return;
    }
    cout << user << ": has " << size << " subscribers " << endl;
    for (unsigned int i=0; i < size; i++) {
        cout << user << " is subscribed to " << sr.subscriptions[i] << endl;
    }
}


int main(int argc, char **argv) {
  if (argc != 4) {
      cerr << "Usage: " << argv[0] << " <tribblerServerIP> <tribblerServerPort> User" << endl;
      exit(0);
  }
  string tribblerServer = string(argv[1]);
  int port = atoi(argv[2]);
  boost::shared_ptr<TSocket> socket(new TSocket(tribblerServer, port));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  TribblerClient client(protocol);
  try {
    transport->open();
    TribbleStatus::type ts_create;
    ts_create = client.CreateUser(argv[3]);
    if (ts_create != TribbleStatus::OK) {
        cout << "Failed to create user: alice. Error code: " << ts_create << endl;
    }

    TribbleResponse tr_alice;
    TribbleStatus::type ts_post;
    string post = argv[3];

    for(int i=0; i < 50; i++)
    {
      string number = boost::lexical_cast<string>(i);
      ts_post = client.PostTribble(argv[3], post + number);
      if (ts_post != TribbleStatus::OK) {
        cout << argv[3] << " could not post "
          << "Error code: " << ts_post << endl;
      }
    }

    transport->close();
  } catch (TException &tx) {
    cout << "ERROR: %s" <<  tx.what() << endl;
  }

  return 0;
}
