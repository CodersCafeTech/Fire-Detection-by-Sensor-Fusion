#include <ESP8266WiFi.h>

const char* ssid = "DARKMATTER";
const char* password = "8848191317";
const char* host = "maker.ifttt.com";

void setup() 
{
    Serial.begin(115200);
    Serial.println("Email from Node Mcu");
    delay(100);
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  
    Serial.println("");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());  
}

void loop() 
{ 

     WiFiClient client; 
     const int httpPort = 80;  
     if (!client.connect(host, httpPort)) 
     {  
       Serial.println("connection failed");  
       return;
     } 
    if(Serial.available( ) > 0) //  It will only send data when the received data is greater than 0.  
   {  
    int receivedData  = Serial.read();  // It will read the incoming or arriving data byte 
    //Serial.println(receivedData,DEC);
    char state = char(receivedData); // print the character for the ASCII value
    //Serial.println(exercise);
    int value = state - '0';
    if(state == '1')
      {
         String url = "";  // Put your url here
         Serial.print("Requesting URL: ");
         Serial.println(url);
         client.print(String("GET ") + url + " HTTP/1.1\r\n" + 
                                    "Host: " + host + "\r\n" +   
                                           "Connection: close\r\n\r\n");    
      }
    
   }  
}
