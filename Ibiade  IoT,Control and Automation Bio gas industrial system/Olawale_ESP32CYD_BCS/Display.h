#define LGFX_ESP32_2432S028
#include <LGFX_AUTODETECT.hpp>
#include <LovyanGFX.hpp>


#include "BG_image.h"
#include "WiFiON_OffIcon.h"
#include "Incoming.h"

bool _x{ false };
float c;

static LGFX lcd;
static LGFX_Sprite sprite(&lcd);


extern const uint8_t BG_image[];
extern const uint8_t On[];
extern const uint8_t Off[];


static constexpr int image_width = 320;
static constexpr int image_height = 240;
static constexpr int Mar_width = 99;
static constexpr int Mar_height = 45;
static constexpr int Wifi_width = 25;
static constexpr int Wifi_height = 35;

void BG_setup() {
  lcd.setColorDepth(1);
  int len = image_width * image_height;
  lcd.setAddrWindow(0, 0, image_width, image_height);
  lcd.writePixels(BG_image, len);
}

void Wifi_MS() {
  lcd.setColorDepth(1);
  int Wlen = Wifi_width * Wifi_height;
  lcd.writePixels(Off, Wlen);
  lcd.writePixels(On, Wlen);
}


void Dis_setup() {
  randomSeed(analogRead(0));

  lcd.init();
  lcd.setRotation(1);
  lcd.startWrite();
  lcd.drawRect(25, 120, 18, 67, 0xF800);

  BG_setup();
}


void display_Rtext() {
  lcd.setTextColor(0x000000U);
  lcd.setTextSize(0.8);
  lcd.fillEllipse(53, 53, 28, 7, 0xffffffU);
  lcd.drawString("TEMP A", 30, 49, &fonts::FreeMono9pt7b);
  lcd.fillEllipse(258, 55, 28, 7, 0xffffffU);
  lcd.drawString("TEMP B", 235, 51, &fonts::FreeMono9pt7b);
  lcd.fillEllipse(76, 114, 28, 7, 0xffffffU);
  lcd.drawString("MOTOR1", 55, 110, &fonts::FreeMono9pt7b);
  lcd.fillEllipse(230, 112, 28, 7, 0xffffffU);
  lcd.drawString("MOTOR2", 205, 108, &fonts::FreeMono9pt7b);

  lcd.fillEllipse(152, 55, 29, 8, 0xffffffU);
  lcd.drawString("HeatMat", 127, 51, &fonts::FreeMono9pt7b);
  lcd.drawString("A", 125, 71, &fonts::FreeMono9pt7b);
  lcd.drawString("B", 125, 98, &fonts::FreeMono9pt7b);
  lcd.drawString("C", 125, 127, &fonts::FreeMono9pt7b);

  lcd.fillEllipse(165, 177, 28, 7, 0xffffffU);
  lcd.drawString("HEATER", 144, 173, &fonts::FreeMono9pt7b);
  lcd.drawString("A", 79, 195, &fonts::FreeMono9pt7b);
  lcd.drawString("B", 137, 195, &fonts::FreeMono9pt7b);
  lcd.drawString("C", 199, 195, &fonts::FreeMono9pt7b);
  lcd.fillEllipse(295, 25, 14, 19, 0xFFFFFFU);
}

void display_Rstext() {
  lcd.setTextColor(0xFFFFFFU);
  lcd.setTextSize(0.5);
  lcd.fillRect(36, 83, 35, 10, 0x4169e1U);
  lcd.fillRect(60, 142, 35, 10, 0x4169e1U);
  lcd.fillRect(241, 85, 35, 10, 0x4169e1U);
  lcd.fillRect(210, 142, 35, 10, 0x4169e1U);
  lcd.drawString("Dig. A", 36, 83, &fonts::FreeMonoBold9pt7b);
  lcd.drawString("Dig. A", 60, 142, &fonts::FreeMonoBold9pt7b);
  lcd.drawString("Dig. B", 241, 85, &fonts::FreeMonoBold9pt7b);
  lcd.drawString("Dig. B", 210, 142, &fonts::FreeMonoBold9pt7b);
}

void HM_temp(int x, int y, int z) {

  lcd.setTextSize(0.4);
  lcd.setFont(&fonts::Font7);
  lcd.setTextColor(0x000000U, 0xFFFFFFU);
  lcd.fillRect(138, 65, 31, 20, 0xFFFFFFU);
  lcd.drawString(String(x), 139, 65);  //a
  lcd.setTextColor(0x000000U, 0xFFFFFFU);
  lcd.fillRect(138, 92, 31, 20, 0xFFFFFFU);
  lcd.drawString(String(y), 139, 92);  //b
  lcd.setTextColor(0x000000U, 0xFFFFFFU);
  lcd.fillRect(138, 122, 31, 20, 0xFFFFFFU);
  lcd.drawString(String(z), 139, 122);  //c
}

void Dig_temp(int v, int w) {

  lcd.setTextSize(0.4);
  lcd.setFont(&fonts::Font7);
  lcd.setTextColor(0x000000U, 0xFFFFFFU);
  lcd.fillRect(29, 62, 40, 20, 0xFFFFFFU);
  lcd.drawString(String(v), 29, 62);  //Dig.a
  lcd.fillRect(233, 64, 40, 20, 0xFFFFFFU);
  lcd.drawString(String(w), 233, 64);  //Dig.b
}

void Motor_Sw(int a, int b) {
  if (a == false) {  //Motor1
    lcd.fillRect(60, 122, 32, 19, 0xFF0000U);
    lcd.setTextColor(0xFFFFFFU);
    lcd.setTextSize(0.8);
    lcd.drawString("OFF", 67, 126, &fonts::FreeMono9pt7b);
  } else {
    lcd.fillRect(60, 122, 32, 19, 0x00CF00U);
    lcd.setTextColor(0xFFFFFFU);
    lcd.setTextSize(0.8);
    lcd.drawString("ON", 68, 126, &fonts::FreeMono9pt7b);
  }
  if ((b == false)) {  //Motor2
    lcd.fillRect(213, 122, 32, 19, 0xFF0000U);
    lcd.setTextColor(0xFFFFFFU);
    lcd.setTextSize(0.8);
    lcd.drawString("OFF", 217, 126, &fonts::FreeMono9pt7b);
  } else {
    lcd.fillRect(213, 122, 32, 20, 0x00CF00U);
    lcd.setTextColor(0xFFFFFFU);
    lcd.setTextSize(0.8);
    lcd.drawString("ON", 220, 126, &fonts::FreeMono9pt7b);
  }
}

void WiFi_InDot(bool sNetwork) {  //

  lcd.fillCircle(270, 24, 6, 0xFFFFFFU);

  if (sNetwork) {  //1
    lcd.fillCircle(270, 24, 5, 0xFF0000U);
  } else {
    lcd.fillCircle(270, 24, 5, 0x00FF00U);
  }
}

void Heater_Sw(int a, int b, int c) {

  lcd.fillRect(88, 190, 32, 20, 0xFFFFFFU);
  lcd.fillRect(146, 190, 32, 20, 0xFFFFFFU);
  lcd.fillRect(208, 190, 32, 20, 0xFFFFFFU);

  if (a == 0) {  //5
    lcd.fillRect(104, 190, 16, 20, 0xFF0000U);
  } else {
    lcd.fillRect(88, 190, 16, 20, 0x00CF00U);
  }
  if (b == 0) {  //6
    lcd.fillRect(162, 190, 16, 20, 0xFF0000U);
  } else {
    lcd.fillRect(146, 190, 16, 20, 0x00CF00U);
  }
  if (c == 0) {  //4
    lcd.fillRect(224, 190, 16, 20, 0xFF0000U);
  } else {
    lcd.fillRect(208, 190, 16, 20, 0x00CF00U);
  }



  delay(1000);
}
