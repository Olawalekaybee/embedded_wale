#include <Wire.h>

const int I2C_SLAVE_ADDRESS = 0x08;
const int I2C_SLAVE_ADDRESS_2 = 0x09;

int wifi_status = 0;
int set_hr = 3;
bool motor1_state = false;
bool motor2_state = false;
int get_hr = 4;





void setupi2c() {
  Wire.begin();
}


void receiveI2c() {
  // Read data from the slave
  uint8_t bytesReceived = Wire.requestFrom(I2C_SLAVE_ADDRESS, sizeof(int) + sizeof(int) + sizeof(int) + sizeof(bool) + sizeof(bool) + 6);


  if (bytesReceived > 0) {

    int set_Min = 1;

    Wire.readBytes((uint8_t *)&set_Min, (sizeof(set_Min) + 2));
    Wire.readBytes((uint8_t *)&set_hr, (sizeof(set_hr) + 2));
    Wire.readBytes((uint8_t *)&get_hr, (sizeof(get_hr) + 2));
    // Wire.readBytes((uint8_t *)&set_threshold, (sizeof(set_threshold) + 2));
    Wire.readBytes((uint8_t *)&motor1_state, (sizeof(motor1_state)));
    Wire.readBytes((uint8_t *)&motor2_state, (sizeof(motor2_state)));





    Serial.print("set_Min: " + String(set_Min));
    Serial.print("set_hr: " + String(set_hr));

    Serial.print("get_hr:" + String(get_hr));
    // Serial.print("set_threshold:" + String(set_threshold));

    Serial.print("motor1_state:" + String(motor1_state));
    Serial.println("motor2_state:" + String(motor2_state));




    Serial.println();
    Serial.println(sizeof(set_Min) + sizeof(set_hr) + sizeof(motor1_state) + sizeof(motor2_state) + sizeof(get_hr));
    delay(1000);
  }
}


void master_sender(int fail, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j, int k, int l, int m, int failure) {
  // Create a character buffer to hold the formatted string
  char buffer[64];
  snprintf(buffer, sizeof(buffer), "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", fail, a, b, c, d, e, f, g, h, i, j, k, l, m, failure);

  // Start the I2C transmission
  Wire.beginTransmission(I2C_SLAVE_ADDRESS);

  // Send the data as bytes
  Wire.write((uint8_t *)buffer, strlen(buffer) + 1);

  // End the I2C transmission and check for errors
  uint8_t result = Wire.endTransmission();
  if (result != 0) {
    Serial.print("Error sending data: ");
    Serial.println(result);
  }

  delay(100);

  Wire.beginTransmission(I2C_SLAVE_ADDRESS_2);
  Wire.write((uint8_t *)buffer, strlen(buffer) + 1);
  uint8_t result2 = Wire.endTransmission();
  if (result2 != 0) {
    Serial.print("Error sending data: ");
    Serial.println(result2);
  }

  delay(50);

  receiveI2c();
}
