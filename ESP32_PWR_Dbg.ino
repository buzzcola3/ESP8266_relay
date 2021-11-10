#include <ESP8266WiFi.h>

#include <RemoteDebug.h>

// RemoteDebug addon library: RemoteDebugger, an Simple software debugger - based on SerialDebug Library

//#include <RemoteDebugger.h>		//https://github.com/JoaoLopesF/RemoteDebugger


#include <RemoteDebugCfg.h>
#include <RemoteDebugWS.h>
#include <telnet.h>
RemoteDebug Debug;

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <AsyncElegantOTA.h>
//.#include "connect.h"
#include "webserver.h"
//#include "chk_request.h"

const char* ssid = "BetakNET5"; // fill in here your router or wifi SSID
const char* password = "Marian228"; // fill in here your router or wifi password
const byte bssid[]={0x50, 0xd2, 0xf5, 0x4e, 0x52, 0xe5}; //MAC adress of target AP

AsyncWebServer userver(8266);

void setup()
{

  // Init the simple software debugger, based on SerialDebug library

  
  pinMode(0, OUTPUT);
  pinMode(3, OUTPUT);
  digitalWrite(0, HIGH);
  digitalWrite(3, LOW);
  
  Serial.begin(115200,SERIAL_8N1, SERIAL_TX_ONLY);
  IPAddress ip(192, 168, 1, 107);
  IPAddress dns(192, 168, 1, 1);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.config(ip, dns, gateway, subnet);
  WiFi.begin(ssid, password, NULL, bssid);

  printerOn('f');
//.  Wconnect();
 
  AsyncElegantOTA.begin(&userver);
  userver.begin();
  server.begin();

  
  Debug.begin("BuZZ"); //debug
  Debug.setResetCmdEnabled(true); //debug
  Debug.showProfiler(true); //debug
  Debug.showColors(true); //debug

  
}

void loop()
{
  AsyncElegantOTA.loop();
  
  webserver();
  //chk_rq();
//.  if (WiFi.status() != WL_CONNECTED){Wconnect();};

Debug.handle(); //debug
yield();
}
