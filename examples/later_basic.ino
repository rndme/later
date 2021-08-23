#include "Arduino.h"
#include "FS.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
ESP8266WebServer server ( 80 );
#include <ESP8266HTTPUpdateServer.h>
ESP8266HTTPUpdateServer httpUpdater;

#include <NTPClient.h>
#include <WiFiUdp.h>
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.nist.gov", -21600, 960000);

// over-ride serial output port from default `Serial`, ex:[ Serial1, ss, NULL (disables uart output)]
#define LATER_UART_PORT Serial
#include <later.h>


void setup() {
  SPIFFS.begin();
  Serial.begin(115200);

  pinMode(0, INPUT_PULLUP);
  pinMode(2, OUTPUT);

  WiFi.disconnect();

  const char* ssid = "the good one"; // put a real SSID here
  const char* password = "ffffffffffff"; // put a real password here

  WiFi.mode(WIFI_STA);
  WiFi.hostname("later_demo");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(150);
    Serial.print(".");
  }

  Serial.println("Online at http://" );
  Serial.println(WiFi.localIP());
  Serial.print("/\nWifi MAC: ");
  Serial.println(WiFi.macAddress());
  server.begin();
  httpUpdater.setup(&server);

  timeClient.begin();
  Serial.println("heap start: " +  String(ESP.getFreeHeap()) );


/////////////////////////////////////////////////////
  if (!digitalRead(0)) {
    Serial.println(F("Later - SAFE MODE ENABLED (no autoexec)"));
  } else {

    Later.addCommand("wipe", [](char * v, LATER_LINE * ln, LATER_ENVIRON * scr )->bool { nsLATER::setRunLog[0] = '\0';  }); // using lambda
    Later.addCommand("myprint", COMMAND( LATER_PRINTLN(value);  )); // using COMMAND MACRO
    Later.addFunction("SUM", [](unsigned long a = 0, unsigned long b = 0, unsigned long c = 0)->unsigned long {return a + b + c;}); // using lambda
    Later.addFunction("PRODUCT", FUNCTION(return (a * b) * (c ? c : 1);)); // using FUNCTION MACRO

    Later.setup();
  } // end if gpio 0 grounded just after startup? don't load scripts (safe mode)
/////////////////////////////////////////////////////

}//end setup()

void loop() {
  timeClient.update();
  server.handleClient();
  Later.loop();
  delay(0);
}