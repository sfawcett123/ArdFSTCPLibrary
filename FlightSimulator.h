#ifndef FLIGHTSIMULATOR_H
	#define FLIGHTSIMULATOR_H

  #define VERSION "0.0.0"
	#include <Arduino.h>
  #include <ArduinoHttpClient.h>  /* https://github.com/arduino-libraries/ArduinoHttpClient */
  #include <WiFiNINA.h>
  #include <ArduinoJson.h>        /* https://arduinojson.org/?utm_source=meta&utm_medium=library.properties */

  #define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(array[0])))

    class FlightSimulator : public HttpClient
    {
        public:
            static const int kHttpPort = 80;
            

            FlightSimulator(Client& aClient, const char* aServerName, uint16_t aServerPort = kHttpPort , const char* aName = "Arduino");
            int Register( String outputs[] );
            void Read( DynamicJsonDocument *SimulatorData );
            void Write(DynamicJsonDocument* SimulatorData);
        private:
            String FlightSimulator::BuildPostData(String outputs[]);
    };

#endif