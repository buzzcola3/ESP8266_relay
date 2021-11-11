#include "fx_handlers.h"
//#include "chk_request.h"
#define relaypin 0


WiFiServer server(80);
AsyncWebServer userver(8266);

unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;

String header;
#include "chk_request.h"
void webserver()
  {
    WiFiClient client = server.available();
    if (client) {                             // If a new client connects,
  
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();         
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {

            chk_rq();
  
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");

            client.println("<body><h1>Ender 3</h1>");

            if (printerOn('?') == 't'){client.println("Printer is On<br>");}
            else {phonepw('r');}   
            
            if (printerOn('?') == 'f') {
              client.println("<p><a href=\"/RELAY=ON\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/RELAY=OFF\"><button class=\"button button2\">OFF</button></a></p>");
            } 
                
            if (printerOn('?') == 't'){client.println("<p><a href=\"/phoneon\"><button class=\"button button2\">phone power</button></a></p>");}

            
            if (printerOn('?') == 't' && phonepw('?') == 't'){client.println("Phone should now be On<br>");} else {client.println((powerbutton_timer + 7000) - millis());}
            client.println("</body></html>");


            } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
                           
 
    return;
  }
