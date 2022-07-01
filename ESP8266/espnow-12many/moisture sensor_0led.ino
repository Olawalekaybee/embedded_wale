#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
 
const int AirValue = 620;   //you need to replace this value with Value_1
const int WaterValue = 310;  //you need to replace this value with Value_2
int soilMoistureValue = 0;
int soilmoisturepercent=0;
void setup() {
  Serial.begin(9600); // open serial port, set the baud rate to 9600 bps
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  display.clearDisplay();
}
void loop() {
soilMoistureValue = analogRead(A0);  //put Sensor insert into soil
Serial.println(soilMoistureValue);
soilmoisturepercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
if(soilmoisturepercent >= 100)
{
  Serial.println("100 %");
  
  display.setCursor(45,0);  //oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Soil");
  display.setCursor(20,15);  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Moisture");
  
  display.setCursor(30,40);  //oled display
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println("100 %");
  display.display();
  
  delay(250);
  display.clearDisplay();
}
else if(soilmoisturepercent <=0)
{
  Serial.println("0 %");
  
  display.setCursor(45,0);  //oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Soil");
  display.setCursor(20,15);  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Moisture");
  
  display.setCursor(30,40);  //oled display
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println("0 %");
  display.display();
 
  delay(250);
  display.clearDisplay();
}
else if(soilmoisturepercent >0 && soilmoisturepercent < 100)
{
  Serial.print(soilmoisturepercent);
  Serial.println("%");
  
  display.setCursor(45,0);  //oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Soil");
  display.setCursor(20,15);  
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Moisture");
  
  display.setCursor(30,40);  //oled display
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println(soilmoisturepercent);
  display.setCursor(70,40);
  display.setTextSize(3);
  display.println(" %");
  display.display();
 
  delay(250);
  display.clearDisplay();
}  
}