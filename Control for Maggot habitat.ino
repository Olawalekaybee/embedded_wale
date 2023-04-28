#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHT_COUNT 2
#define MINIMUM_AUTOTUNE_DEGREES 10
#define MAXIMUM_AUTOTUNE_DEGREES 100
#define sw_Humid 10
#define sw_cool 11
#define sw_Mode 8
#define coolPin 6
#define humidPin 12
#define input_read 3

int totalColumns = 16;
int dhtPins[DHT_COUNT] = { 2, 3 };
int potPins[] = { A2, A3 };
int targetTemperature = 22;                          // default target Temperature In AUTO Mode
int targetHumidity = 60;                             // default target humidity In AUTO Mode
int controlPins[] = { sw_Mode, sw_Humid, sw_cool };  //readpin_H, readCool_pin
int actuator[] = { coolPin, humidPin };              // CoolPin, humidPin;
String scrollingMessage = " ";

LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C 1602 LCD display;

DHT_Unified dhts[DHT_COUNT] = {
  DHT_Unified(dhtPins[0], DHT22),
  DHT_Unified(dhtPins[1], DHT22)

};

float temperatures[DHT_COUNT];
float humidities[DHT_COUNT];


namespace Insect_Habitat {
bool Mode(int a);
void scrollMessage(int a, String b, int c, int d, bool e);
}

void Insect_Habitat::scrollMessage(int row, String message, int delayTime, int totalColumns, bool mode) {
  if (mode == false) {

    for (int i = 0; i < totalColumns; i++) {
      message = " " + message;
    }
    message = message + " ";
    for (int position = 0; position < message.length(); position++) {
      lcd.setCursor(9, row);
      lcd.print(message.substring(position, position + totalColumns));
      delay(delayTime);
    }
  } else {
    lcd.setCursor(9, row);
    lcd.print("Manual M0de");
    delay(delayTime + 100);
  }
}

bool Insect_Habitat::Mode(int a) {
  bool x = (digitalRead(a) == HIGH) ? true : false;
  return x;
}

void setup() {
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Maggot Habitat ");

  for (int i; i < input_read; i++) {
    pinMode(controlPins[i], INPUT_PULLUP);
  }

  for (int i; i < (input_read - 1); i++) {
    pinMode(actuator[i], OUTPUT);
    digitalWrite(actuator[i], LOW);
  }

  for (int i = 0; i < DHT_COUNT; ++i) {
    dhts[i].begin();
  }

  delay(1000);
}

void loop() {

  Insect_Habitat::Mode(controlPins[0]);  // check if the swith is either auto or manual State;
  bool w = Insect_Habitat::Mode(controlPins[0]);
  readTemperatureHumidity();
  showDisplay(w);
  handleAuto(1, w);
}



void readTemperatureHumidity() {
  for (int i = 0; i < DHT_COUNT; ++i) {
    sensors_event_t event;
    dhts[i].temperature().getEvent(&event);
    if (isnan(event.temperature)) {

      temperatures[i] = -1;

    } else {

      temperatures[i] = event.temperature;
    }
    dhts[i].humidity().getEvent(&event);
    if (isnan(event.relative_humidity)) {

      humidities[i] = -1;
    } else {

      humidities[i] = event.relative_humidity;
    }
  }
}

void handleAuto(int x, bool y) {

  targetTemperature = map(analogRead(potPins[0]), 0, 1023, MINIMUM_AUTOTUNE_DEGREES, MAXIMUM_AUTOTUNE_DEGREES);  // varing potentiometer for adjusting Temp
  targetHumidity = map(analogRead(potPins[1]), 0, 1023, MINIMUM_AUTOTUNE_DEGREES, MAXIMUM_AUTOTUNE_DEGREES);     // varing potentiometer  for adjusting humidity
  if (y == false) {
    for (int i = 0; i < x; i++) {
      digitalWrite(actuator[0], (temperatures[i] >= targetTemperature) ? LOW : HIGH);  // Auto Mode operation for compressor ON/Off
      digitalWrite(actuator[1], (humidities[i] >= targetHumidity) ? LOW : HIGH);       // Auto Mode operation for Humidifier ON/Off
    }
  } else if (y == true) {

    digitalWrite(actuator[0], (digitalRead(controlPins[2]) == LOW) ? HIGH : LOW);  // Manual Mode operation for compressor ON/Off
    digitalWrite(actuator[1], (digitalRead(controlPins[1]) == LOW) ? HIGH : LOW);  // Manual Mode operation for Humidifier ON/Off
  }
}


void showDisplay(bool m) {
  //for (unsigned long start = millis(); millis() - start < 1000;) {
  scrollingMessage = "MODE: AUTO ";
  scrollingMessage += "Set T:" + String(targetTemperature) + " " + "Set H:" + String(targetHumidity);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(String("T1:") + String(temperatures[0]) + " " + String("T2:") + String(temperatures[1]));
  lcd.setCursor(0, 1);
  lcd.print(String("H1:") + String(humidities[0]));
  Insect_Habitat::scrollMessage(1, scrollingMessage, 400, totalColumns, m);
  //}
  delay(500);
}