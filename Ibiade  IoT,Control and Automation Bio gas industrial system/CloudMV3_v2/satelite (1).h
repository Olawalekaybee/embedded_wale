#include <TinyGPS++.h>
#include <SoftwareSerial.h>


TinyGPSPlus gps;
SoftwareSerial gpsSerial(16, 17);

// GPS and Time Variables
double lat, lng, alt;
String date, tim;


int ch = 0;
int cm = 0;
int chs, cms;

bool trigger_set = false;
void initialize_gps() {
  gpsSerial.begin(9600);
}


void getGps() {
  boolean newData = false;

  // Read GPS data for 1 second
  unsigned long start = millis();
  while (millis() - start < 1000) {
    while (gpsSerial.available() > 0) {
      if (gps.encode(gpsSerial.read())) {
        newData = true;
        break;
      }
    }
    if (newData) break;
  }

  // Process new GPS data
  if (newData) {
    lat = gps.location.lat();
    lng = gps.location.lng();
    // date = String(gps.date.month()) + "/" + String(gps.date.day()) + "/" + String(gps.date.year());
    chs = gps.time.hour() + 1;  // No need to add 1 unless it's required for specific reasons
    cms = gps.time.minute();
    tim = String(chs) + ":" + String(cms);


  } else {
    lat = 0;
    lng = 0;
  }
}
