#include <Wire.h>
#include "seperator.h"


const int I2C_SLAVE_ADDRESS = 0x09;
bool checK_incom = false;
String receivedString = "";


void receiveEvent(int howMany) {
  while (Wire.available()) {
    char c = Wire.read();
    receivedString += c;
  }
}


void intslavesetup() {
  Wire.setPins(22, 27);
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
 
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
