#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_NeoPixel.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"



#define NUMPIXELS 200

#define PIN 6
#define DELAYVAL 10

#define DHTPIN 9
#define DHTTYPE    DHT22


DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int lastTime = 0;
int timerDelay = 500;

float temp, hum, IR;
int HT;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
MAX30105 particleSensor;

const byte RATE_SIZE = 4; 
byte rates[RATE_SIZE]; 
long lastBeat = 0; 

float beatsPerMinute;
int beatAvg;
long irValue;

void setup()
{
  Serial.begin(115200);
  pixels.begin();

  lcd.begin(16, 2);

  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  

  while (!Serial); 
  delay(100);
  Serial.println("");
  Serial.println("MAX30102");
  Serial.println("");
  delay(100);

  if (particleSensor.begin(Wire, I2C_SPEED_FAST) == false) {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);

}


void loop() {

  Neomellopad1();
  DH_T();
  heartbeat();
  disp2();
}

void DH_T() {
  if ((millis() - lastTime) > timerDelay) {

    sensors_event_t event;
    dht.temperature().getEvent(&event);
    temp = (temp, ((!isnan(event.temperature))) ? event.temperature : 0); 
    dht.humidity().getEvent(&event);
    hum = (hum, ((!isnan(event.relative_humidity))) ? event.relative_humidity : 0);
    lastTime = millis();
  }
}



void Neomellopad1() {
  for (int i = 0; i < NUMPIXELS; i++) { 
    pixels.setPixelColor(i, pixels.Color(0, 0, 139));
    pixels.show();
  }
}


void disp2()
{
  lcd.setCursor(0, 0);

  lcd.print(String("H:") + String((hum, 1) + String("%"));
  lcd.setCursor(9, 0);
  lcd.print(String("T:") + String(temp, 1) + String("C"));

  lcd.setCursor(0, 1);
  lcd.print(String("AVg_HBM:") + String((HT, ((irValue > 50000)) ? beatAvg : "No cont?"), 1));//

}


void heartbeat() {

  irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true)
  {
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute;
      rateSpot %= RATE_SIZE; 

     
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }


  if (irValue < 50000)
    Serial.print(" No finger?");

  Serial.println();
}
