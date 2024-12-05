#include "Display.h"
#include "walenet.h"

// bool _x{ false };

void setup() {
  Serial.begin(115200);
  setup_wifi();
  Dis_setup();
  intslavesetup();


  display_Rstext();
  display_Rtext();
}

void loop() {
  outputData();

  for (int i = 0; i < data_counter; i++) {
    Serial.println("output{" + String(i) + "}->" + in_data[i]);
  }
  
   bool recheck = (ping("www.google.com")) ? true : false;
   bool hotspot_con = (WiFi.status() != WL_CONNECTED) ? false : true;
   bool connectivity = ((recheck == true) && (hotspot_con == true)) ? true : false;
  if ((!hotspot_con)) {  //true
    lcd.setColorDepth(8);
    lcd.pushImage(283, 9, Wifi_width, Wifi_height, (lgfx::rgb332_t*)Off, 0);
  } else {
    lcd.setColorDepth(8);
    lcd.pushImage(283, 9, Wifi_width, Wifi_height, (lgfx::rgb332_t*)On, 0);
  }

  Wifi_MS();
  Motor_Sw(in_data[6].toInt(), in_data[7].toInt());
  Heater_Sw(in_data[8].toInt(), in_data[9].toInt(), in_data[10].toInt());
  WiFi_InDot(!connectivity);

  Dig_temp(in_data[1].toInt(), in_data[2].toInt());
  HM_temp(in_data[3].toInt(), in_data[4].toInt(), in_data[5].toInt());
}



bool ping(const char* host) {
  WiFiClient client;
  if (client.connect(host, 80)) {
    client.stop();
    return true;
  }
  return false;
}