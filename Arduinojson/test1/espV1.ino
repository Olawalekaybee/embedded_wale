#define CAYENNE_PRINT Serial
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <CayenneMQTTESP8266.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

char cayenneUsername[] = "a2154070-d0f8-11ea-883c-638d8ce4c23d";
char cayennePassword[] = "6d8033bf1abacfcfc891792e94877f3d3b31f737";
char cayenneClientID[] = "ec615570-d895-11ea-93bf-d33a96695544";

char blynkAuth[] = "7CNuuBNP_0_wisjawj3LLh4EShHCXhRu";

//char wifiID[] = "Airtel 4G Router_17DC";
//char wifiPassword[] = "meyanabioenergy202@";

char wifiID[] = "MoDivine";
char wifiPassword[] = "Lead7383";

bool isFirstSample[2];
bool wasConnectedToWiFi, wasConnectedToBlynk, wasConnectedToCayenne;
long tWatch[3];
StaticJsonDocument<256> memory;
SoftwareSerial terminal_1(D7, D2);
SoftwareSerial terminal_0(D5, D6);

void setup() {
  isFirstSample[0] = isFirstSample[1] = true;
  wasConnectedToWiFi = wasConnectedToCayenne = wasConnectedToBlynk = false;

  Serial.begin(115200);

  terminal_0.begin(115200, SWSERIAL_8N1);
  terminal_1.begin(115200, SWSERIAL_8N1);

  Cayenne.begin(cayenneUsername, cayennePassword, cayenneClientID, wifiID, wifiPassword);
  Blynk.begin(blynkAuth, wifiID, wifiPassword);
  tWatch[0] = tWatch[1] = tWatch[2] = millis() + 5000;
}

void loop() {
  checkWiFiConnection();
  checkBlynkConnection();

  if (isFirstSample[0])  isFirstSample[0] = false;

  if (terminal_0.available() > 0)  {
    collect(0);
  }

  if (terminal_1.available() > 0)  {
    collect(1);
  }

  terminal_0.write(1);
  terminal_1.write(1);
}

void collect(int terminalId) {
  DynamicJsonDocument dataIn(512), JsonNull(256);
  if (terminalId == 0)  {
    deserializeJson(dataIn, terminal_0);
  }
  if (terminalId == 1)  {
    deserializeJson(dataIn, terminal_1);
  }
  //  serializeJson(dataIn, Serial);
  //  Serial.println();

  unsigned int a, k, chnl;
  float value;

  deserializeJson(JsonNull, "[null]");

  if ((dataIn == JsonNull[0]) || !dataIn.containsKey("s")) return;
  if (dataIn["s"].as<JsonArray>().size() < 4) return;

  if (isFirstSample[1])  {
    a = 0;
    isFirstSample[1] = false;
  }
  else if (memory[dataIn["id"]] != JsonNull[0])  {
    a = memory[dataIn["id"]]["start"];
  }
  else  {
    a = 0;
    for (int i = 0; i < memory.as<JsonArray>().size(); i++) {
      if (memory[i] == JsonNull[0]) continue;
      a = (memory[i]["start"] >= a) ? int(memory[i]["start"]) + int(memory[i]["bandwidth"]) : a;
    }
  }
  k = 0;
  for (int i = 0; i < dataIn["s"].as<JsonArray>().size(); i++) {
    k += (i == 0) ? 0 : dataIn["s"][i - 1];
    for (int j = 0; j < dataIn["s"][i]; j++) {
      chnl = a + k + j;
      String key = (i == 0) ? "t" : (i == 1) ? "p" : (i == 2) ? "ph" : "l";
      if (dataIn[key][j] == JsonNull[0]) continue;
      value = dataIn[key][j];
      if (i == 0)  {
        const char type[] = "temp";
        const char unit[] = "c";
        Cayenne.virtualWrite(chnl, value, type, unit);
        Blynk.virtualWrite((chnl == 0) ? V0 : (chnl == 1) ? V1 : (chnl == 2) ? V2 : (chnl == 3) ? V3 : (chnl == 4) ? V4 : (chnl == 5) ? V5 : (chnl == 6) ? V6 : V7, value);
      }
      else if (i == 1) {
        const char type[] = "press";
        const char unit[] = "pa";
        Cayenne.virtualWrite(chnl, value, type, unit);
        Blynk.virtualWrite((chnl == 0) ? V0 : (chnl == 1) ? V1 : (chnl == 2) ? V2 : (chnl == 3) ? V3 : (chnl == 4) ? V4 : (chnl == 5) ? V5 : (chnl == 6) ? V6 : V7, value);
      }
      else if (i == 2) {
        const char type[] = "acid";
        const char unit[] = "acid";
        Cayenne.virtualWrite(chnl, value, type, unit);
        Blynk.virtualWrite((chnl == 0) ? V0 : (chnl == 1) ? V1 : (chnl == 2) ? V2 : (chnl == 3) ? V3 : (chnl == 4) ? V4 : (chnl == 5) ? V5 : (chnl == 6) ? V6 : V7, value);
      }
      else if (i == 3) {
        const char type[] = "tl";
        const char unit[] = "null";
        Cayenne.virtualWrite(chnl, 200.0 - value, type, unit);
        Blynk.virtualWrite((chnl == 0) ? V0 : (chnl == 1) ? V1 : (chnl == 2) ? V2 : (chnl == 3) ? V3 : (chnl == 4) ? V4 : (chnl == 5) ? V5 : (chnl == 6) ? V6 : V7, 200 - value);
      }
    }
  }
  memory[dataIn["id"]]["start"] = a;
  memory[dataIn["id"]]["bandwidth"] = chnl + 1 - a;
}

void checkWiFiConnection(void)  {
  if (WiFi.status() != WL_CONNECTED) {
    if ((tWatch[0] - millis() <= 0) || isFirstSample[0] || wasConnectedToWiFi)  {
      WiFi.begin(wifiID, wifiPassword);
      tWatch[0] = millis() + 5000;
      if (wasConnectedToWiFi)  {
        //        Serial.println("Oops!... I Got Disconnected from the WiFi.");
        wasConnectedToWiFi = false;
      }
    }
  }
  else  {
    if (!wasConnectedToWiFi)  {
      //      Serial.println("I'm now Connected to the WiFi.");
      wasConnectedToWiFi = true;
    }
  }
}

CAYENNE_DISCONNECTED() {
  if ((tWatch[1] - millis() <= 0) || isFirstSample[0] || wasConnectedToCayenne)  {
    Cayenne.begin(cayenneUsername, cayennePassword, cayenneClientID, wifiID, wifiPassword);
    tWatch[1] = millis() + 5000;
    if (wasConnectedToCayenne)  {
      //      Serial.println("Oops!... I Got Disconnected from Cayenne.");
      wasConnectedToCayenne = false;
    }
  }
}

CAYENNE_CONNECTED() {
  if (!wasConnectedToCayenne)  {
    //    Serial.println("I'm now Connected to Cayenne.");
    wasConnectedToCayenne = true;
  }
}

void checkBlynkConnection(void)  {
  if (!Blynk.connected()) {
    if ((tWatch[2] - millis() <= 0) || isFirstSample[0] || wasConnectedToBlynk)  {
      Blynk.begin(blynkAuth, wifiID, wifiPassword);
      tWatch[2] = millis() + 5000;
      if (wasConnectedToBlynk)  {
        //        Serial.println("Oops!... I Got Disconnected from Blynk.");
        wasConnectedToBlynk = false;
      }
    }
  }
  else  {
    if (!wasConnectedToBlynk)  {
      //      Serial.println("I'm now Connected to Blynk.");
      wasConnectedToBlynk = true;
    }
  }
}