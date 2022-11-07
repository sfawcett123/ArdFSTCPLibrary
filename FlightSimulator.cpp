#include "FlightSimulator.h"

String contentType = "application/json";
String postData ;
String url = "/api/simulator/register";

char *boardName ;

StaticJsonDocument<100> json_data;
StaticJsonDocument<100> response_data;

Client* xWifiClient;

FlightSimulator::FlightSimulator(Client& aClient, const char* aServerName, uint16_t aServerPort , const char* aName )
   : HttpClient(aClient, aServerName , aServerPort)
{
  xWifiClient = &aClient;
  boardName =  aName ;
}

void FlightSimulator::BuildPostData( String outputs[] )
{
  json_data["name"]       =  boardName;
  json_data["os_system"]  = "Arduino";
  json_data["os_version"] =  VERSION;

  JsonArray data = json_data.createNestedArray("outputs");

  for (int i = 0; i < ARRAY_SIZE(outputs); i++) {
    data.add( outputs[i] ) ;
  }
  serializeJson( json_data , postData );
}

int FlightSimulator::Register( String outputs[] )
{
  BuildPostData( outputs );

  post( url, contentType, postData);

  int statusCode = responseStatusCode();
  String response = responseBody();

  Serial.print("Status code: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);

  DeserializationError error = deserializeJson(response_data, response);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }

  char* port = response_data["port"];

  return String( port ).toInt();
}

void FlightSimulator::Read( DynamicJsonDocument *SimulatorData)
{
  DeserializationError error = deserializeJson( *SimulatorData, *xWifiClient);
 
}


