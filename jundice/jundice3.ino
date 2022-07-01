#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_NeoPixel.h>
//#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"

//LiquidCrystal_I2C lcd(0x27, 16, 2);

#define NUMPIXELS 200
//#define ONE_WIRE_BUS 7
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

float temp, hum, IR, HT;

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
MAX30105 particleSensor;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

void setup()
{
  Serial.begin(115200);
  pixels.begin();

  //lcd.init();
  lcd.begin(16, 2);
  // lcd.print("hello");
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  //delayMS = sensor.min_delay / 1000;

  while (!Serial); //We must wait for Teensy to come online
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

  //  byte ledBrightness = 70;
  //  byte sampleAverage = 1;
  //  byte ledMode = 2;
  //  int sampleRate = 400;
  //  int pulseWidth = 69;
  //  int adcRange = 16384;
  //particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings

}


void loop() {

  Neomellopad1();
  DH_T();
  // disp();
  //htb();
  heartbeat();
  disp2();
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

//void disp()
//{
//
//  lcd.backlight();
//  lcd.setCursor(0, 0);
//  //int ran = random(2, 40);
//  lcd.print(String(ran));
//  lcd.print(String("Hum:") + String(hum) + String("%"));
//  lcd.setCursor(0, 1);
//  // lcd.print(String("ran"));
//  lcd.print(String("Temp:") + String(temp) + String("C"));
//
//}

void disp2()
{
  lcd.setCursor(0, 0);

  lcd.print(String("H:") + String(hum, 1) + String("%"));
  lcd.setCursor(9, 0);
  lcd.print(String("T:") + String(temp, 1) + String("C"));

  lcd.setCursor(0, 1);
  lcd.print(String("HBEAT:") + String(beatAvg, 1));

}

//void htb() {
//  particleSensor.check();
//  while (particleSensor.available()) {
//    IR = particleSensor.getFIFOIR();
//    Serial.print(IR);
//    Serial.print(",");
//    HT = particleSensor.getFIFORed();
//    Serial.println(HT);
//
//    particleSensor.nextSample();
//  }
//}

void heartbeat() {

  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true)
  {
    //We sensed a beat!
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

//  Serial.print("IR=");
//  Serial.print(irValue);
//  Serial.print(", BPM=");
//  Serial.print(beatsPerMinute);
//  Serial.print(", Avg BPM=");
//  Serial.print(beatAvg);

  if (irValue < 50000)
    Serial.print(" No finger?");

  Serial.println();
}
