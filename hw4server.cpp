
// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "hw4server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "hw4client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

// ecs36b
#include "IOT_Thing.h"
#include "Person.h"
#include "Thing.h"
#include <time.h>
#include "Shadow_Thing.h"

using namespace jsonrpc;
using namespace std;

class Myhw4Server : public hw4Server
{
public:
  Myhw4Server(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value dump2JSON(const std::string& action, const std::string& arguments, const std::string& class_id, const std::string& host_url, const std::string& object_id);
};

Myhw4Server::Myhw4Server(AbstractServerConnector &connector, serverVersion_t type)
  : hw4Server(connector, type)
{
  std::cout << "Myhw4Server Object created" << std::endl;
}

Thing *thing_ptr;

// member functions

Json::Value
Myhw4Server::dump2JSON
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id)
{
  Json::Value result;
  std::cout << action << " " << arguments << std::endl;
  std::string strJson;

  if ((class_id != "Thing") || (object_id != "00000001"))
    {
      result["status"] = "failed";
      if (class_id != "Thing")
	{
	  strJson = ( "class " + class_id + " unknown");
	}
      else
	{
	  strJson = ( "object " + object_id + " unknown");
	}
      result["reason"] = strJson;
    }
  else
    {
      result = thing_ptr->dump2JSON();
      result["status"] = "successful";
    }

  return result;
}

int main()
{
  GPS_DD gps_Home_Woodland { 38.672215864622636, -121.72280111121437 };
  GPS_DD gps_TLC_UCDavis   { 38.53874868013882,  -121.7542091083306 };
  GPS_DD gps_IKEA_Sacramento { 38.58681641563053, -121.55296296578501};

  Person Felix { "987654321", "Felix", gps_Home_Woodland };
  Felix.setLocation(gps_IKEA_Sacramento, (*getNowJvTime()));

  IP_Address meatball_IP { 2850883174 };
  IOT_Thing Swedish_Meatball { Felix , meatball_IP };
  
  Swedish_Meatball.model = "HUVUDROLL";
  Swedish_Meatball.sequence_num = "123456-0000";
  Swedish_Meatball.description = "frozen";
  Swedish_Meatball.location = gps_Home_Woodland;
  Swedish_Meatball.purchased = *getNowJvTime();
  Swedish_Meatball.sold = *getNowJvTime();
  Swedish_Meatball.owner = Felix;

  thing_ptr = (Thing *) (&Swedish_Meatball);

  HttpServer httpserver(8384);
  Myhw4Server s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
