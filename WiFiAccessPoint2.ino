/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>


  
// Set these to your desired credentials.
const char *ssid = "Pride";
const char *password = "yourPassword";

WiFiServer server(80);

#define up 13
#define down 12
#define left 27
#define right 14
#define clockwise 32
#define counterclockwise 35
#define forward 33
#define backward 34

void setup() {
  pinMode (up, OUTPUT);
  pinMode (down, OUTPUT);
  pinMode (left, OUTPUT);
  pinMode (right, OUTPUT);
  pinMode (clockwise, OUTPUT);
  pinMode (counterclockwise, OUTPUT);
  pinMode (forward, OUTPUT);
  pinMode (backward, OUTPUT);
  
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("welcome to Ian's quad control page <br>");
            client.print("<button><a href=\"/u\">up</a> <button><br>");
            client.print("<button><a href=\"/d\">down</a> <button><br>");
            client.print("<button><a href=\"/l\">left</a> <button><br>");
            client.print("<button><a href=\"/r\">right</a> <button><br>");
            client.print("<button><a href=\"/c\">clockwise</a> <button><br>");
            client.print("<button><a href=\"/cc\">counter clockwise</a> <button><br>");
            client.print("<button><a href=\"/f\">forward</a> <button><br>");
            client.print("<button><a href=\"/b\">backward</a> <button><br>");
            client.print("<button><a href=\"/s\">stop</a> <button><br>");
             
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /u")) {
            up();
               
        }
        if (currentLine.endsWith("GET /d")) {
            down();                 
        }
         if (currentLine.endsWith("GET /l")) {
            left();         
      }
      if (currentLine.endsWith("GET /r")) {
            righ(); 
     } 
      if (currentLine.endsWith("GET /c")) {
            counter();         
      } 
       if (currentLine.endsWith("GET /cc")) {
            counterclockwise();         
      } 
       if (currentLine.endsWith("GET /b")) {
            backward();         
      } 
       if (currentLine.endsWith("GET /f")) {
            forward();         
      }            
         
       }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

void forward(){
  digitalWrite(forward, HIGH);
  digitalWrite(backwards, LOW);
  digitalWrite(up, LOW);
  digitalWrite(down, LOW);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
  digitalWrite(clockwise, LOW);
  digitalWrite(counterclockwise, LOW);
}
void backward(){
  digitalWrite(forward, LOW);
  digitalWrite(backwards, HIGH);
  digitalWrite(up, LOW);
  digitalWrite(down, LOW);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
  digitalWrite(clockwise, LOW);
  digitalWrite(counterclockwise, LOW);
}
void up(){
  digitalWrite(forward, LOW);
  digitalWrite(backwards, LOW);
  digitalWrite(up, HIGH);
  digitalWrite(down, LOW);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
  digitalWrite(clockwise, LOW);
  digitalWrite(counterclockwise, LOW);
}
void down(){
  digitalWrite(forward, LOW);
  digitalWrite(backwards, LOW);
  digitalWrite(up, LOW);
  digitalWrite(down, HIGH);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
  digitalWrite(clockwise, LOW);
  digitalWrite(counterclockwise, LOW);
}
void left(){
  digitalWrite(forward, LOW);
  digitalWrite(backwards, LOW);
  digitalWrite(up, LOW);
  digitalWrite(down, LOW);
  digitalWrite(left, HIGH);
  digitalWrite(right, LOW);
  digitalWrite(clockwise, LOW);
  digitalWrite(counterclockwise, LOW);
}
void right(){
  digitalWrite(forward, LOW);
  digitalWrite(backwards, LOW);
  digitalWrite(up, LOW);
  digitalWrite(down, LOW);
  digitalWrite(left, LOW);
  digitalWrite(right, HIGH);
  digitalWrite(clockwise, LOW);
  digitalWrite(counterclockwise, LOW);
}
void clockwise(){
  digitalWrite(forward, LOW);
  digitalWrite(backwards, LOW);
  digitalWrite(up, LOW);
  digitalWrite(down, LOW);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
  digitalWrite(clockwise, HIGH);
  digitalWrite(counterclockwise, LOW);
}
void counterclockwise(){
  digitalWrite(forward, LOW);
  digitalWrite(backwards, LOW);
  digitalWrite(up, LOW);
  digitalWrite(down, LOW);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
  digitalWrite(clockwise, LOW);
  digitalWrite(counterclockwise, HIGH);
}
void allstop(){
  digitalWrite(forward, LOW);
  digitalWrite(backwards, LOW);
  digitalWrite(up, LOW);
  digitalWrite(down, LOW);
  digitalWrite(left, LOW);
  digitalWrite(right, LOW);
  digitalWrite(clockwise, LOW);
  digitalWrite(counterclockwise, LOW);
}
