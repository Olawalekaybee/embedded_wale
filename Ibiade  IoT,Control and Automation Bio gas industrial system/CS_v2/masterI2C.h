#include "Wire.h"
#define I2C_DEV_ADDR 0x55
float biot1 = 20.0;
float bioT2 = 30.0;
float tha = 40.10;
float thb = 50.50;
float thc = 60.90;
int ha = 1;
int hb = 0;
int hc = 1;
int motor1 = 1;
int motor2 = 1;

void setupI2C() {
  // Serial.begin(115200);
  Wire.begin();
}



void I2Crw() {
 delay(50);
  // Write the floats to the slave
  Wire.beginTransmission(I2C_DEV_ADDR);
  Wire.write((uint8_t *)&biot1, sizeof(biot1));
  Wire.write((uint8_t *)&bioT2, sizeof(bioT2));
  Wire.write((uint8_t *)&tha, sizeof(tha));
  Wire.write((uint8_t *)&thb, sizeof(thb));
  Wire.write((uint8_t *)&thc, sizeof(thc));
  Wire.write((uint8_t *)&ha, sizeof(ha));
  Wire.write((uint8_t *)&hb, sizeof(hb));
  Wire.write((uint8_t *)&hc, sizeof(hc));
  Wire.write((uint8_t *)&motor1, sizeof(motor1));
  Wire.write((uint8_t *)&motor2, sizeof(motor2));

  // Wire.write((uint8_t *)&dht, sizeof(dht));
  // Wire.write((uint8_t *)&co2, sizeof(co2));
  // Wire.write((uint8_t *)&ldr, sizeof(ldr));

  uint8_t result = Wire.endTransmission(true);
  if (result != 0) {
    Serial.print("Error sending data: ");
    Serial.println(result);
  }


  // Optionally, you can read data from the slave
  // uint8_t bytesReceived = Wire.requestFrom(I2C_DEV_ADDR, 17); // 16 bytes for floats + 1 byte for bool
  // Serial.printf("requestFrom: %u\n", bytesReceived);

  // Read data from the slave
  uint8_t bytesReceived = Wire.requestFrom(I2C_DEV_ADDR, sizeof(int) + sizeof(bool));  //sizeof(float)--> 16 bytes for floats + 4 bytes for count + 1 byte for bool
  Serial.print("requestFrom:" + String(bytesReceived));

  if (bytesReceived > 0) {  // If received more than zero bytes
    //uint8_t temp[16]; // 16 bytes for floats
    uint8_t wifi_status;  // 1 byte for the bool
    int count;            // to read count


    //Wire.readBytes(temp, 16); // Read float data
    Wire.readBytes((uint8_t *)&count, sizeof(count));  // Read count
    Wire.readBytes(&wifi_status, 1);                   // Read boolean status

    Serial.println("Data Acknowledged");
    Serial.print("Count: " + String(count));  // Print as integer
    Serial.print("WiFi Status:" + String(wifi_status));
    Serial.println();
  }
}