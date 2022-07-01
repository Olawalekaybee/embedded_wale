#include <ESP8266WiFi.h>
#include <espnow.h>


uint8_t broadcastAddress[] = {0x24, 0x6F, 0x28, 0x7A, 0xAE, 0x7C};
uint8_t broadcastAddress1[] = {0x48, 0x3F, 0xDA, 0x35, 0xCE, 0x9E};//48:3F:DA:35:CE:9E

uint8_t* Transmitter[] ={broadcastAddress, broadcastAddress1};


typedef struct struct_message {
  char a[32];
  int b;
  float c;
  String d;
  bool e;
} struct_message;

// Create a struct_message called myData
struct_message myData;

unsigned long lastTime = 0;  
unsigned long timerDelay = 2000;  // send readings timer

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  //esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
 // esp_now_add_peer(broadcastAddress1, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);//
  for (int i= 0; i<2; i++) {
    esp_now_add_peer(Transmitter[i], ESP_NOW_ROLE_SLAVE, 1, NULL, 0);//
  }
}
 
void loop() {
  if ((millis() - lastTime) > timerDelay) {
    // Set values to send
    strcpy(myData.a, "THIS IS A CHAR");
    myData.b = random(1,20);
    myData.c = 1.2;
    myData.d = "Hello";
    myData.e = false;

    // Send message via ESP-NOW
    // esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    // esp_now_send(broadcastAddress1, (uint8_t *) &myData, sizeof(myData));

    for (int i= 0; i<2; i++) {
    esp_now_send(Transmitter[i], (uint8_t *) &myData, sizeof(myData));
  }
    lastTime = millis();
  }
}