#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define NUMPIXELS 16
#define ONE_WIRE_BUS 7
#define PIN 6
#define DELAYVAL 10

#define DHTPIN 9
#define DHTTYPE    DHT22


DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

int lastTime = 0;
int timerDelay = 500;

float temp, hum;



Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


void setup()
{
  Serial.begin(115200);
  pixels.begin();
  lcd.init();
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
}
void loop() {

  Neomellopad1();
  DH_T();
  disp();
}

void DH_T() {
  if ((millis() - lastTime) > timerDelay) {

    sensors_event_t event;
    dht.temperature().getEvent(&event);
    temp = event.temperature;
    if (isnan(event.temperature)) {
      Serial.println(F("Error reading temperature!"));
    }
    else {
      Serial.print(F("Temperature: "));

      Serial.print(temp);
      Serial.println(F("°C"));
    }
    // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    hum = event.relative_humidity;
    if (isnan(event.relative_humidity)) {
      Serial.println(F("Error reading humidity!"));
    }
    else {
      Serial.print(F("Humidity: "));
      Serial.print(hum);
      Serial.println(F("%"));
    }
    lastTime = millis();
  }
}



void Neomellopad1() {
  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(0, 0, 139));// blue  off
    pixels.show();
  }
}

void disp()
{
 
  lcd.backlight();
  lcd.setCursor(0, 0); 
  lcd.print(String("Hum:") + String(hum) + String("%"));
  lcd.setCursor(0, 1);
   lcd.print(String("Temp:") + String(temp) + String("C"));

}

