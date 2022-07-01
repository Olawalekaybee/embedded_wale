#include <BasicEncoder.h>
#include <EEPROM.h>
#include <Adafruit_GFX.h>   // Core graphics library by Adafruit
#include <Arduino_ST7789.h> // Hardware-specific library for ST7789 (with or without CS pin)
#include <SPI.h>

#define HEATER_COUNT 3
#define TEMPERATURE_INCREMENT 5
#define SCREEN_COUNT 6
#define TEMP_SENSORS_REFRESH_INTERVAL 2000

#define TFT_DC 48
#define TFT_RST 49

#define BUTTON_PIN 15
#define ENCODER1_PIN 16
#define ENCODER2_PIN 17

#define MOTOR_RELAY_PIN 23

int heaterRelayPins[HEATER_COUNT] = {6, 5, 4};
int getTemp[3]; //

#define SCREEN_INFO 0
#define SCREEN_TEMP1_CONTROL 1
#define SCREEN_TEMP2_CONTROL 2
#define SCREEN_TEMP3_CONTROL 3
#define SCREEN_MOTOR_CONTROL 4
#define SCREEN_HEATER_CONTROL 5

BasicEncoder encoder(ENCODER1_PIN, ENCODER2_PIN);
Arduino_ST7789 tft = Arduino_ST7789(TFT_DC, TFT_RST); // for display without CS pin

int temperatures[HEATER_COUNT];
int targetTemperatures[HEATER_COUNT];
int extruderTemperature;
boolean motorActive = false;
boolean heatersActive = true; //
unsigned long lastSensorUpdate = 0;

#include "temp_util.h"

boolean needRefresh = true; //
long oldPosition = 0;
int selection = 0;
int optionCount = 5;
int screen = SCREEN_INFO;
boolean editMode = false;

#define check 20

unsigned long lastTime = 0;
unsigned long timerDelay = 200;

void setup()
{
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(MOTOR_RELAY_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  tft.init(240, 240);
  tft.fillScreen(BLACK);
  for (int i = 0; i < HEATER_COUNT; ++i)
  {
    targetTemperatures[i] = EEPROM.read(i);
  }
  for (int i = 0; i < HEATER_COUNT; ++i)
  {
    pinMode(heaterRelayPins[i], OUTPUT);
  }
}

void loop()
{
  updateEncoder();
  updateScreen();
  updateSensors();
  // setRelays();
  //sh();
}

void updateScreen()
{
  if ((needRefresh))
  {

    tft.fillScreen(BLACK);
    switch (screen)
    {
      case SCREEN_INFO:
        showInfoScreen();
        break;
      case SCREEN_TEMP1_CONTROL:
        showTemperatureControlScreen(0);
        break;
      case SCREEN_TEMP2_CONTROL:
        showTemperatureControlScreen(1);
        break;
      case SCREEN_TEMP3_CONTROL:
        showTemperatureControlScreen(2);
        break;
      case SCREEN_MOTOR_CONTROL:
        showMotorControlScreen();
        break;
      case SCREEN_HEATER_CONTROL:
        showHeaterControlScreen();
        break;


    }
    needRefresh = false; // changed
    // BUGFIX: encoder library gives false readings going backwards on large delays
    encoder.service();
    oldPosition = encoder.get_count();
    // END BUGFIX
  }
  //  }


}

void updateSensors()
{
  if (millis() - lastSensorUpdate < TEMP_SENSORS_REFRESH_INTERVAL)
  {
    return;
  }
  int tmp;
  for (int i = 0; i < HEATER_COUNT; ++i)
  {
    tmp = readTemp(i);
    if (heatersActive == true)
    {
      digitalWrite(heaterRelayPins[i], ((targetTemperatures[i]) >= (readTemp(i) + (HEATER_COUNT * 0.25))) ? HIGH : LOW);
    }
    else
    {
      digitalWrite(heaterRelayPins[i], LOW);
    }
    if (temperatures[i] != tmp)
    {
      if (screen == SCREEN_INFO || (screen - 1) == i)
      {
        needRefresh = true;
      }
    }
    temperatures[i] = tmp;
  }
  tmp = (3);
  if (extruderTemperature != tmp)
  {
    if (screen == SCREEN_INFO)
    {
      needRefresh = true;
    }
  }
  extruderTemperature = tmp;
  lastSensorUpdate = millis();
}

void updateEncoder()
{

  encoder.service();

  long newPosition = encoder.get_count();
  if (newPosition != oldPosition)
  {
    //Serial.println(String("old:") + oldPosition + " new:" + newPosition);
    onEncoderChange((newPosition > oldPosition) ? 1 : -1);

  }
  if (!digitalRead(BUTTON_PIN))
  {
    delay(10);
    while (!digitalRead(BUTTON_PIN))
      ;
    delay(10);
    onEncoderClick();
  }

}

void showInfoScreen()
{

  tft.setCursor(0, 0);
  tft.setTextSize(3);
  tft.setTextColor(BLUE);
  tft.println("Info Screen\n");
  for (int i = 0; i < HEATER_COUNT; ++i)
  {
    tft.setTextSize(2);
    tft.setTextColor(MAGENTA);
    tft.print("Heater #");
    tft.println(i + 1);
    tft.setTextSize(2);
    tft.setTextColor(GREEN);
    tft.print("Curr:");
    tft.setTextColor(RED);
    tft.print(temperatures[i]);
    tft.setTextColor(GREEN);
    tft.print(" Target:");
    tft.setTextColor(RED);
    tft.println(targetTemperatures[i]);
  }

  tft.setTextSize(2);
  tft.setTextColor(MAGENTA);
  tft.setTextColor(RED);
  tft.println(extruderTemperature);

  tft.setTextSize(2);
  tft.setTextColor(MAGENTA);
  tft.print("Motor: ");
  tft.setTextColor(RED);
  tft.println(motorActive ? "ON" : "OFF");

  tft.setTextColor(MAGENTA);
  tft.print("Heaters: ");
  tft.setTextColor(RED);
  tft.println(heatersActive ? "ON" : "OFF");

  // delay(1000);

}

void showTemperatureControlScreen(int heaterId)
{
  tft.setCursor(0, 0);
  tft.setTextSize(3);
  tft.setTextColor(BLUE);
  tft.print("Temperature\nControl #");
  tft.println(heaterId + 1);
  tft.println();

  tft.setTextSize(2);
  tft.setTextColor(MAGENTA);
  tft.print("Current: ");
  tft.setTextColor(GREEN);
  tft.println(temperatures[heaterId]);
  // Serial.println(temperatures[heaterId]);

  tft.println();
  tft.setTextColor(MAGENTA);
  tft.println("      Target\n");
  if (editMode)
  {
    tft.setTextColor(RED);
  }
  else
  {
    tft.setTextColor(GREEN);
  }
  tft.setTextSize(4);
  tft.print("    ");
  tft.println(targetTemperatures[heaterId]);
}

void showMotorControlScreen()
{
  tft.setCursor(0, 0);
  tft.setTextSize(3);
  tft.setTextColor(BLUE);
  tft.println("Motor\nControl\n");

  tft.setTextSize(4);
  tft.setTextColor(editMode ? RED : GREEN);
  tft.print(motorActive ? "  " : " ");
  tft.println(motorActive ? "ACTIVE" : "INACTIVE");
}

void showHeaterControlScreen()
{
  tft.setCursor(0, 0);
  tft.setTextSize(3);
  tft.setTextColor(BLUE);
  tft.println("Heater\nControl\n");

  tft.setTextSize(4);
  tft.setTextColor(editMode ? RED : GREEN);
  tft.print(heatersActive ? "  " : " ");
  tft.println(heatersActive ? "ACTIVE" : "INACTIVE");
}

void onEncoderChange(int dir)
{
  //Serial.println(String("onEncoderChange()") + dir);
  // Serial.println(String("editMode:") + (editMode ? "ON" : "OFF"));
  if (editMode)
  {
    switch (screen)
    {
      case SCREEN_INFO:
        break;
      case SCREEN_TEMP1_CONTROL:
        targetTemperatures[0] = constrain(targetTemperatures[0] + dir * TEMPERATURE_INCREMENT, 0, 200);
        EEPROM.write(0, targetTemperatures[0]);
        break;
      case SCREEN_TEMP2_CONTROL:
        targetTemperatures[1] = constrain(targetTemperatures[1] + dir * TEMPERATURE_INCREMENT, 0, 200);
        EEPROM.write(1, targetTemperatures[1]);
        break;
      case SCREEN_TEMP3_CONTROL:
        targetTemperatures[2] = constrain(targetTemperatures[2] + dir * TEMPERATURE_INCREMENT, 0, 200);
        EEPROM.write(2, targetTemperatures[2]);
        break;
      case SCREEN_MOTOR_CONTROL:
        motorActive = !motorActive;
        digitalWrite(MOTOR_RELAY_PIN, motorActive);
        //Serial.println(String("motor set to:") + (motorActive ? "ACTIVE" : "INACTIVE"));
        break;
      case SCREEN_HEATER_CONTROL:
        heatersActive = !heatersActive;
        break;
    }

  }
  else
  {
    screen = (screen + dir + SCREEN_COUNT) % SCREEN_COUNT;
  }
  needRefresh = true; //
}

void onEncoderClick()
{
  if ((screen != SCREEN_INFO))
  {
    editMode = !editMode;

    needRefresh = true;
  }
}

void setRelays()
{

  for (int i = 0; i < HEATER_COUNT; ++i)
  {
    if (heatersActive == true)
    {
      digitalWrite(heaterRelayPins[i], ((targetTemperatures[i]) >= (readTemp(i) + (HEATER_COUNT * 0.25))) ? HIGH : LOW);
    }
    else
    {
      digitalWrite(heaterRelayPins[i], LOW);
    }
  }
}

void sh() {

  if ((heatersActive == true) || (heatersActive == false)) {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println(LED_BUILTIN);
    delay(1000);                       //
    Serial.println(LED_BUILTIN);
    delay(1000);
  }
}