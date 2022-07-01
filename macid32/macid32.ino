#include "WiFi.h" // AC:67:B2:09:16:38

 
void setup() {

  Serial.begin(115200);

  WiFi.mode(WIFI_MODE_STA);
 
 
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}
 
void loop() {
 
}
