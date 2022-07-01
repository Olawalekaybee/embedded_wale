#include<Meyana.h>

#define MAX_D 400
#define MAX_T 45.0
#define MIN_T 30.0
#define SCREEN_ADDRESS_C 0x23
#define NODE_ADDRESS 0
#define MY_ID 2

Temperature t(MIN_T, MAX_T);
PH pH(1, A0);
Display s(1, SCREEN_ADDRESS_C);
Caster c(MY_ID);

void setup()    {
  Serial.begin(115200);

  t.configureTempProbes(1, 9);
  t.configureTempControls(1, 2, A1);
  attachInterrupt(digitalPinToInterrupt(t.thermostat[0].pin[0]), temp_ISR, FALLING);
  t.setHeaterDistribution(1, 2);
  unsigned int h[] = {10, 11};
  t.configureHeaterPins(1, h);

  m.configureMotorControls(1, 3, 4, 5);
  attachInterrupt(digitalPinToInterrupt(m.motor[0].pin[0]), motor_ISR, FALLING);

  s.configureDisplays();

  c.configureCaster(&t, NULL, &pH, NULL);

  //  c.resetNode(A6);
}

void loop() {
  t.readTemperatures();
  t.updateHeaters();

  pH.readPHValues(100);

  s.display(&t, NULL, &pH, NULL);

  c.cast(&t, &p, &pH, &l, false);
}

void temp_ISR()  {
  int i = 0;
  float tStart = millis();
  while(digitalRead(t.thermostat[0].pin[0]) == LOW) {
    t.MAX_TEMP[0] += (digitalRead(t.thermostat[0].pin[1]) == HIGH) ? 1.0 : -1.0;
    if((millis() - tStart >= 3000) && (i < 5)) {
      tStart = millis();
      i += 1;
    }
    delay(500 - (100 * i));
  }
}
