#include "controlTempHeat.h"
#include "controlMotors.h"
#include "mI2C.h"

int _hrs = 4;
int _mins = 5;
int heaterState0, heaterState1, heaterState2;
int motorstate0, motorstate1;
int hsafezoneH0 = 50;

int hsafezoneH1 = 50;

void setup() {
  Serial.begin(115200);
  setupi2c();
  config_T();
  set_hdist();
  init_isr_m();
  setup_M();
}

void loop() {
  bio_Temperature();
  heater_Temperature();
  _hrs = get_hr;
  motorstate0 = (digitalRead(activate_M) == HIGH) ? 1 : 0;
  motorstate1 = (digitalRead(activate_M_1) == HIGH) ? 1 : 0;

  heaterState0 = (digitalRead(heaters[0]) == HIGH) ? 1 : 0;
  heaterState1 = (digitalRead(heaters[1]) == HIGH) ? 1 : 0;
  heaterState2 = (digitalRead(heaters[2]) == HIGH) ? 1 : 0;

  set_Hsafezone(hsafezoneH0, hsafezoneH1);  // depends on the heaters 0 & 1 temperatures

  heatdistributor(temp[0], Min_T, Max_T);    // relies on (internal and heatmat temperature)
  heatdistributor1(temp[1], Min_T, Max_T);   // relies on (internal and heatmat temperature)
  heatdistributor2(Htemp[2], (Max_T - 10));  // greater than 37 "off" ? "ON" ( rely on heatmat temp)
  ctrl_Motors(motor1_state, motor2_state);   // completed here
  master_sender(0, temp[0], temp[1], Htemp[0], Htemp[1], Htemp[2], motorstate0, motorstate1, heaterState0, heaterState1, heaterState2, _hrs, _mins, 0, 0);
  // debug_temperature();
  // debug_heaters();
  // debug_motor();
}


void debug_temperature() {
  Serial.print("bioTemp{0}: ");
  Serial.print(temp[0]);
  Serial.print("bioTemp{1}: ");
  Serial.println(temp[1]);

  Serial.println("//////// digester Temperature////////////////////////////");
  Serial.print("Heater Temp{0}: ");
  Serial.print(Htemp[0]);
  Serial.print("Heater Temp{1}: ");
  Serial.print(Htemp[1]);
  Serial.print("Heater Temp{2}: ");
  Serial.println(Htemp[2]);
  Serial.println("/////////////End HeaterTemperatures///////////////////////");
}

void debug_heaters() {
  Serial.print((heaterState0 == true) ? "ON " : "OFF  ");
  Serial.print((heaterState0 == true) ? "ON " : "OFF  ");
  Serial.println((heaterState0 == true) ? "ON " : "OFF ");
  Serial.println("/////////////////End Heaters////////////////////////");
}

void debug_motor() {
  Serial.print((motorstate0 == true) ? "ON " : "OFF  ");
  Serial.println((motorstate1 == true) ? "ON " : "OFF  ");

  Serial.println("/////////////////End Motor////////////////////////");
}