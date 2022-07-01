#include  "Arduino.h"

const int AirValue = 545;
const int WaterValue = 216;
int soilMoistureValue = 0;
int soilmoisturepercent = 0;
void setup() {
  Serial.begin(115200); //
}
void loop() {
  soilMoistureValue = analogRead(A0);
 // Serial.println(soilMoistureValue);
  soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  if (soilmoisturepercent >= 100)
  {
    Serial.println("100 %");
  }
  else if (soilmoisturepercent <= 0)
  {
    Serial.println("0 %");
  }
  else if (soilmoisturepercent > 0 && soilmoisturepercent < 100)
  {
    Serial.print(soilmoisturepercent);
    Serial.println("%");

  }
  delay(250);
}