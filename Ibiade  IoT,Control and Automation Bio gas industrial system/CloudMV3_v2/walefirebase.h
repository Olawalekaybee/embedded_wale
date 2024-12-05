#if defined(ARDUINO_ARCH_ESP8266)
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#elif defined(ARDUINO_ARCH_ESP32)
#include <WiFi.h>
#include <WebServer.h>
#endif


#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"




#if defined(ARDUINO_ARCH_ESP8266)
ESP8266WebServer Server;
#elif defined(ARDUINO_ARCH_ESP32)
WebServer Server;
#endif
#define WIFI_SSID "olawale"
#define WIFI_PASSWORD "olawale33"


#define API_KEY "AIzaSyAKe4XJ_2DK-EO_psvGJR7fRJ1DVCAgxTk";                                     //"AIzaSyBUSJfnWz_V4zbhEdn1pC2ucPlYQaLjp5M"  //"AIzaSyDHeMMYbb8g2MHPnENzKEeovGB3sRA89Oc"
#define DATABASE_URL "https://version2dgstr-default-rtdb.europe-west1.firebasedatabase.app/";  //"https://walmv3-default-rtdb.europe-west1.firebasedatabase.app/"  //"https://concreteproject1-dd849-default-rtdb.europe-west1.firebasedatabase.app/"
#define CREDENTIAL_OFFSET 0
#include <Array.h>
Array<int, 4> _Data;


unsigned long sendDataPrevMillis = 0;




bool signupOK = false;
bool state{ true };
bool start_con = false;
bool network_isp{ false };
bool check_connect{ false };



FirebaseData fbdo;


FirebaseAuth auth;
FirebaseConfig config;






void setup_firebase(bool x) {




  if (x == true) {


    config.api_key = API_KEY;


    config.database_url = DATABASE_URL;




    if (Firebase.signUp(&config, &auth, "", "")) {
      Serial.println("ok");
      signupOK = true;
    } else {
      Serial.printf("%s\n", config.signer.signupError.message.c_str());
    }


    config.token_status_callback = tokenStatusCallback;


    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
  }
}








void setup_internet(int x) {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  delay(x);
  check_connect = (WiFi.status() == WL_CONNECTED) ? true : false;
}




void setup_initialize_firebase() {
  network_isp = true;


  if (network_isp) {


    setup_internet(3000);
    setup_firebase(state);
  }
}




void send_data_to_firebase(float a, float b, int c, int d, float e, float f, float g, int h, int i, int j, int k, int l) {


  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 2000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    Firebase.RTDB.setFloat(&fbdo, "AD_Digester/Temperature_0", 0.0 + a);
    Firebase.RTDB.setFloat(&fbdo, "AD_Digester/Temperature_1", 0.0 + b);

    Firebase.RTDB.setInt(&fbdo, "AD_Digester/Motor_A", 0.0 + c);
    Firebase.RTDB.setInt(&fbdo, "AD_Digester/Motor_B", 0.0 + d);

    Firebase.RTDB.setFloat(&fbdo, "Heatmat/TemperatureA", 0.0 + e);
    Firebase.RTDB.setFloat(&fbdo, "Heatmat/TemperatureB", 0.0 + f);
    Firebase.RTDB.setFloat(&fbdo, "Heatmat/TemperatureC", 0.0 + g);

    Firebase.RTDB.setInt(&fbdo, "Heatmat/HeaterA", 0.0 + h);
    Firebase.RTDB.setInt(&fbdo, "Heatmat/HeaterB", 0.0 + i);
    Firebase.RTDB.setInt(&fbdo, "Heatmat/HeaterC", 0.0 + j);

    Firebase.RTDB.setInt(&fbdo, "OperatingTime/hry", 0.0 + k);
    Firebase.RTDB.setInt(&fbdo, "OperatingTime/mns", 0.0 + l);
  }
}


void read_from_firebase() {


  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 2000 || sendDataPrevMillis == 0)) {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getInt(&fbdo, "/Read_Data/Activate")) {
      if (fbdo.dataType() == "int") {
        _Data[0] = fbdo.intData();
      }
    }

    if (Firebase.RTDB.getInt(&fbdo, "/Read_Data/MotorA")) {
      if (fbdo.dataType() == "int") {
        _Data[1] = fbdo.intData();
      }
    }
    if (Firebase.RTDB.getInt(&fbdo, "/Read_Data/MotorB")) {
      if (fbdo.dataType() == "int") {
        _Data[2] = fbdo.intData();
      }
    }

    if (Firebase.RTDB.getInt(&fbdo, "/Read_Data/Sethr")) {
      if (fbdo.dataType() == "int") {
        _Data[3] = fbdo.intData();
      }
    }
  }
}








void checkWiFiConnection() {
  for (unsigned long start = millis(); millis() - start < 500;) {
    if ((WiFi.status() != WL_CONNECTED)) {
      // Portal.begin();
      //Serial.println("WiFi connected: " + WiFi.localIP().toString());
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      delay(500);
      Firebase.reconnectWiFi(true);
    }
  }
}
