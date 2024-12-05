#include <Wire.h>
#include "seperator.h"
#include "walefirebase.h"
#include "fetchTime.h"

const int I2C_SLAVE_ADDRESS = 0x08;
bool checK_incom = false;
String receivedString = "";
int set_Min = 0;
int set_hr = 0;
int get_hr = 0;
bool motor1_state = false;
bool motor2_state = false;


void receiveEvent(int howMany) {
  while (Wire.available()) {
    char c = Wire.read();
    receivedString += c;
  }
}
void onRequest() {
  set_Min = minutes;
  set_hr = hours;
  motor1_state = ((adj == 1) || (_Data[1] == 1)) ? true : false;
  motor2_state = ((adj0 == 1) || (_Data[2] == 1)) ? true : false;
  get_hr = (_Data[3] == NULL) ? 4 : _Data[3];  // read hrs from firebase
 

  Wire.write((uint8_t *)&set_Min, sizeof(set_Min));  // Send set_Min as bytes
  Wire.write((uint8_t *)&set_hr, sizeof(set_hr));    // Send set_Min as bytes
  Wire.write((uint8_t *)&get_hr, sizeof(get_hr));
  Wire.write((uint8_t *)&motor1_state, sizeof(motor1_state));  //
  Wire.write((uint8_t *)&motor2_state, sizeof(motor2_state));


  Serial.println(sizeof(set_Min) + sizeof(set_hr) + sizeof(motor1_state) + sizeof(motor2_state) + sizeof(get_hr) );
}

void intslavesetup() {
  Wire.setPins(21, 22);
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(onRequest);
}

void outputData() {

  if (receivedString.length() > 0) {
    separate_words(receivedString);
    receivedString = " ";
    checK_incom = true;
  } else {
    checK_incom = false;
  }
}
