

#include <NTPClient.h>
#include <WiFiUdp.h>
#include "satelite.h"
// Initialize WiFi and NTP Client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000);  // GMT, update every 60 seconds
int hours, minutes;
int Timer_h, Timer_m;

int adj;
int adj0 = 0;  // added


void setup_time(bool x) {
  if (x == true) {
    timeClient.begin();
  }
}

int prog(int hr, int set_hr, int rm, int m_on) {

  Timer_h = ((hr % set_hr) == 0) ? 1 : 0;
  Timer_m = (rm < m_on) ? 1 : 0;
  adj = ((Timer_h == 1) && (Timer_m == 1)) ? 1 : 0;

  ////////////start///////////////
  if ((Timer_h == 1)) {
    if ((rm >= m_on) && (rm <= (2 * m_on))) {

      adj0 = 1;
    } else {
      adj0 = 0;
    }
  } else {
    adj0 = 0;
  }
  //////////////end ////////////
  return adj;
}

void update_tim(bool x) {

  if (x == true) {

    // Get current hours and minutes
    timeClient.update();
    hours = timeClient.getHours() + 1;
    minutes = timeClient.getMinutes();



  } else {

    hours = chs;
    minutes = cms;
  }
}


