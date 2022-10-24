
#include "Shadow_Thing.h"

// JSON RPC part
#include "hw4client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

Shadow_Thing::Shadow_Thing
(std::string arg_host_url, std::string arg_class_id, std::string arg_object_id)
{
  this->host_url = arg_host_url;
  this->class_id = arg_class_id;
  this->object_id = arg_object_id;
  std::cout << "Shadow_Thing Object created" << std::endl;
}

Json::Value
Shadow_Thing::dump2JSON()
{
  HttpClient httpclient((this->host_url).c_str());
  hw4Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;

  try {
    Json::Value p;
    p["action"] = "dump2JSON";
    p["class_id"] = class_id;
    p["host_url"] = host_url;
    p["object_id"] = object_id;

    myv = myClient.dump2JSON("dump2JSON", "anything you prefer",
			     (this->class_id).c_str(), (this->host_url).c_str(),
			     (this->object_id).c_str());

    cout << myv.toStyledString() << endl;
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  
  return myv;
}

