/*
 * HTTPClient lib --  Performing an HTTP POST to our REST service
 *
 * Remark:
 * - Going through ngrok
 *
 */
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "John🐻";
const char* password = "abete555";

const char *serviceURI = "https://fbdf-87-19-93-97.eu.ngrok.io";

void connectToWifi(const char* ssid, const char* password){
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200); 
  connectToWifi(ssid, password);
}

int sendData(String address, float value, String place){  
  
   HTTPClient http;    
   http.begin(address + "/api/data");      
   http.addHeader("Content-Type", "application/json");    
    
   String msg = 
    String("{ \"value\": ") + String(value) + 
    ", \"place\": \"" + place +"\" }";
   
   int retCode = http.POST(msg);   
   http.end();  
      
   return retCode;
}

void loop() {
  if (WiFi.status()== WL_CONNECTED){      

    int value = random(15,200);
    int code = sendData(serviceURI, value, "home");
    if (code == 200){
       Serial.println("ok");   
     } else {
       Serial.println(String("error: ") + code);
     }
    
    delay(5000);

  } else {
    Serial.println("WiFi Disconnected... Reconnect.");
    connectToWifi(ssid, password);
  }
}
