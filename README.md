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
