#include <WiFi.h>
#define WIFI_SSID "olawale"
#define WIFI_PASSWORD "olawale33"


void setup_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  if (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }
 
}


void checkWiFiConnection() {
  for (unsigned long start = millis(); millis() - start > 5000;) {

    if ((WiFi.status() != WL_CONNECTED)) {
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      delay(500);
    }
    start = millis();
  }
}