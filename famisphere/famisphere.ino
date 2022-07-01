
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
// Define to which pin of the Arduino the 1-Wire bus is connected:
#define ONE_WIRE_BUS 13
// Create a new instance of the oneWire class to communicate with any OneWire device:
OneWire oneWire(ONE_WIRE_BUS);
// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensors(&oneWire);
int deviceCount = 0;
float tempC;
#define DHTPIN 14   // Digital pin connected to the DHT sensor
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
DHT_Unified dht(DHTPIN, DHTTYPE);
#define buzzer 12
uint32_t delayMS;
void setup() {
  // Begin serial communication at a baud rate of 9600:
 Serial.begin(9600);
 lcd.init();                      // initialize the lcd
 lcd.backlight();
  // Start up the library:
  sensors.begin();
  // Locate the devices on the bus:
  Serial.println("Locating devices...");
  Serial.print("Found ");
  deviceCount = sensors.getDeviceCount();
  Serial.print(deviceCount);
  Serial.println(" devices");
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  pinMode (buzzer, OUTPUT);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  delayMS = sensor.min_delay / 1000;
 
}
void loop() {
 ds18b20();
 dht22();
 
 ///T1
 if (sensors.getTempCByIndex(0)> 35){ //It should be 4 degrees
 digitalWrite(buzzer, HIGH);
 delay(1000);
 digitalWrite(buzzer, LOW);
 }
 else
 //T2
 digitalWrite(buzzer, LOW);
 if (sensors.getTempCByIndex(1)> 40){ //It should be 10 degrees
 digitalWrite(buzzer, HIGH);
 delay(1000);
 digitalWrite(buzzer, LOW);
 }
 else
digitalWrite(buzzer, LOW);
}



void ds18b20 (void){
  // Send the command for all devices on the bus to perform a temperature conversion:
  sensors.requestTemperatures();
  // Display temperature from each sensor
  for (int i = 0;  i < deviceCount;  i++) {
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(" : ");
    tempC = sensors.getTempCByIndex(i);
    Serial.print(tempC);
    Serial.print(" \xC2\xB0"); // shows degree symbol
    Serial.println("C");
   lcd.setCursor(0,0);
   lcd.print("T1 "); lcd.print(sensors.getTempCByIndex(0));
   lcd.print(" T2 "); lcd.print(sensors.getTempCByIndex(1));
   
  }
}

void dht22 (void){
      delay(delayMS);
  // Get temperature event and print its value.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    Serial.print(F("Ambient Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  // Get humidity event and print its value.
    dht.humidity().getEvent(&event);
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    lcd.setCursor(0,1);
    lcd.print("T3 "); lcd.print(event.temperature);
    lcd.print(" H1 "); lcd.print(event.relative_humidity);
  }
