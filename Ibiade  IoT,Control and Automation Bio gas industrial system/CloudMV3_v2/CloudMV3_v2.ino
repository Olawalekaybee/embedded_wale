#include "incoming.h"



void setup() {
  Serial.begin(115200);

  intslavesetup();
  setup_initialize_firebase();
  setup_time(check_connect);

  delay(2000);
}



void loop() {
  outputData();
  delay(100);

  check_connect = (WiFi.status() == WL_CONNECTED) ? true : false;
  update_tim(check_connect);


  float temp0 = in_data[1].toFloat();
  float temp1 = in_data[2].toFloat();
  float Htemp0 = in_data[3].toFloat();
  float Htemp1 = in_data[4].toFloat();
  float Htemp2 = in_data[5].toFloat();

  int motorstate0 = in_data[6].toInt();
  int motorstate1 = in_data[7].toInt();
  int heaterState0 = in_data[8].toInt();
  int heaterState1 = in_data[9].toInt();
  int heaterState2 = in_data[10].toInt();
  int _hrs = (in_data[11].toInt() == NULL) ? 4 : in_data[11].toInt();
  int _mins = (in_data[12].toInt() == NULL) ? 5 : in_data[12].toInt();

  prog(abs(hours), _hrs, abs(minutes), _mins);
  bool recheck = (ping("www.google.com")) ? true : false;
  Serial.print("ping: ");
  Serial.println(recheck);

  checkWiFiConnection();
  send_data_to_firebase(temp0, temp1, motorstate0, motorstate1, Htemp0, Htemp1, Htemp2, heaterState0, heaterState1, heaterState2, _hrs, _mins);
  read_from_firebase();
}


bool ping(const char* host) {
  WiFiClient client;
  if (client.connect(host, 80)) {
    client.stop();
    return true;
  }
  return false;
}