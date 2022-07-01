#include <esp_now.h>
#include <WiFi.h>


typedef struct struct_message {
  int id;
  int x;
  bool y;
}struct_message;


struct_message myData;

struct_message board1;
struct_message board2;


struct_message boardsStruct[2] = {board1, board2};


void OnDataRecv(const uint8_t * mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.printf("Board ID %u: %u bytes\n", myData.id, len);
  
  boardsStruct[myData.id-1].x = myData.x;
  boardsStruct[myData.id-1].y = myData.y;
  Serial.printf("x value: %d \n", boardsStruct[myData.id-1].x);
  Serial.printf("y value: %d \n", boardsStruct[myData.id-1].y);
  Serial.println();
}
 
void setup() {
 
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);

 
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
 
  /*int board1X = boardsStruct[0].x;
  bool board1Y = boardsStruct[0].y;
  int board2X = boardsStruct[1].x;
  bool board2Y = boardsStruct[1].y;
  */


}
