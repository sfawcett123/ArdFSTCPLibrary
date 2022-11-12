#include "FlightSimulator.h"

String contentType = "application/json";
String url = "/api/simulator/register";

char *boardName ;

StaticJsonDocument<1000> response_data;

Client* xWifiClient;

FlightSimulator::FlightSimulator(Client& aClient, const char* aServerName, uint16_t aServerPort , const char* aName )
   : HttpClient(aClient, aServerName , aServerPort)
{
  xWifiClient = &aClient;
  boardName =  aName ;
}

String FlightSimulator::BuildPostData( String outputs[] )
{
  String postData;
  DynamicJsonDocument json_data( 1024 );

  json_data["name"]       =  boardName;
  json_data["os_system"]  = "Arduino";
  json_data["os_version"] =  VERSION;

  JsonArray data = json_data.createNestedArray("outputs");

  for (int i = 0; i < ARRAY_SIZE(outputs); i++) {
    data.add( outputs[i] ) ;
  }
  serializeJson( json_data , postData );
  return postData;
}

int FlightSimulator::Register( String outputs[] )
{
  String postData = BuildPostData( outputs );

  post( url, contentType, postData);

  int statusCode = responseStatusCode();
  String response = responseBody();

  if (statusCode < 0) return statusCode;

  DeserializationError error = deserializeJson(response_data, response);

  if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return -1;
  }

  char* port = response_data["port"];

  return String( port ).toInt();
}

void FlightSimulator::Read( DynamicJsonDocument *SimulatorData)
{
  DeserializationError error = deserializeJson( *SimulatorData, *xWifiClient);
 
}

void FlightSimulator::Write(DynamicJsonDocument* SimulatorData)
{
    DeserializationError error = serializeJson(*SimulatorData, *xWifiClient);

}


