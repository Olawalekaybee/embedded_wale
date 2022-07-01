#include <ESP8266WiFi.h>
#include <espnow.h>


uint8_t broadcastAddress[] = {0x8C, 0xAA, 0xB5, 0x7A, 0xB8, 0xAE};
#define BOARD_ID 2 //2

const int AirValue = 550; //
const int WaterValue = 276;
int soilMoistureValue = 0;
int soilmoisturepercent = 0;


int val;
int s;

typedef struct struct_message {
  int id;
  int x;
  int y;
} struct_message;


struct_message myData;

unsigned long lastTime = 0;
unsigned long timerDelay = 1000;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("\r\nLast Packet Send Status: ");
  if (sendStatus == 0) {
    Serial.println("Delivery success");
  }
  else {
    Serial.println("Delivery fail");
  }
}

void setup() {
  // Init Serial Monitor
  Serial.begin(115200);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  // Set ESP-NOW role
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);


  esp_now_register_send_cb(OnDataSent);


  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

}

void loop() {
  
  readings(10000);
  sender();
}


void readings(int re) {
  soilMoistureValue = analogRead(A0);
  for (int i = 0; i < re; ++i) {
    s = soilMoistureValue;
  }
  val = s;
  soilmoisturepercent = map(val, AirValue, WaterValue, 0, 100);
  Serial.println(soilmoisturepercent);
}

void sender() {
  if ((millis() - lastTime) > timerDelay) {
    // Set values to send
    myData.id = BOARD_ID;
    myData.x = soilmoisturepercent;
    myData.y = random(1, 50);

    // Send message via ESP-NOW
    esp_now_send(0, (uint8_t *) &myData, sizeof(myData));
    lastTime = millis();
    // readings(10000);
  }
}
