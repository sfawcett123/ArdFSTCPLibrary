# ArdFSTCPLibrary
Arduino Flight Simulator TCP Library

## Purpose
This library provides routines to enable a WiFi enables Arduino Uno to connect to the [Flight Simulator Listener](https://github.com/sfawcett123/FlightSimulator).

## Required Libraries
- https://github.com/arduino-libraries/ArduinoHttpClient
- https://www.arduino.cc/reference/en/libraries/wifinina/
- https://arduinojson.org/?utm_source=meta&utm_medium=library.properties

## Functions

### Constructor

FlightSimulator(Client , ServerName, ServerPort , BoardName )

  - Wifi Client. I have not tested this with anyother network clients yet.
  - ServerName. IP address or Name of the Sim Listener Server
  - ServerPort. Port that the Sim listener REST API is listening on
  - BoardName. A unique name for this board.
  
### Methods

int Register( outputs[] )

  - Returns the port that will provide the data
  - Outputs. A String array containing a list of SIMVARS i.e {"PLANE ALTITUDE" , "PLANE LATITUDE" }

void Read( *SimulatorData )

  - SimulatorData is a pointer to a [DynamicJsonDocument](https://arduinojson.org/?utm_source=meta&utm_medium=library.properties) object. This will contain the data read from the Flight Simulator, and can be accessed using SimulatorData["PLANE ALTITUDE"] 

void Write( *SimulatorData )

  - SimulatorData is a pointer to a [DynamicJsonDocument](https://arduinojson.org/?utm_source=meta&utm_medium=library.properties) object. This will contain the data read from the Flight Simulator, and can be accessed using SimulatorData["PLANE ALTITUDE"] 

## Simple Example

```C
#include <SPI.h>
#include <WiFiNINA.h>
#include "FlightSimulator.h"

#include "<LOCATION OF YOUR SECRETS>\secrets.h"

int status = WL_IDLE_STATUS;
int ListenPort = 0;

String RequiredOutputs[1] = {"PLANE ALTITUDE"};
DynamicJsonDocument SimulatorData(100) ;

WiFiClient wifi;
// HOST_NAME is the name of the SimListener Server
// PORT is the REST API interface port 
FlightSimulator fsclient = FlightSimulator( wifi , HOST_NAME , HOST_PORT );

void setup() {
   Serial.begin(9600); // Start Serial Interface
}

void loop() {

  if( status == WL_CONNECTED )
  {   
    if( !fsclient.connected())
    {
      Serial.println( "Registering");
      ListenPort = fsclient.Register( RequiredOutputs ); // Register your board and get a PORT back
      if( ListenPort > 0 )
      {
        wifi.connect(  HOST_NAME , ListenPort ); // Connect to that PORT so you can send and recieve data
        Serial.println( "Connected to host");
      }
    }

    if( fsclient.connected())
    {
      fsclient.Read(&SimulatorData) ;   // Read data
      fsclient.Write(&SimulatorData) ;  // Write it back as an example
    }

    String Altitude = SimulatorData["PLANE ALTITUDE"];
    Serial.println( Altitude );
  }
  else
  {
    delay(5000);
    status = WiFi.begin(ssid, pass); // Connect to WiFi 
  } 
  delay(1000);
}
```
