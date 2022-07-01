#include <PID_v2.h>
#define WINDOW_SIZE 5000

double Kp = 2, Ki = 5, Kd = 1;
unsigned long windowStartTime;

PID_v2 pids[HEATER_COUNT] = {
  PID_v2(Kp, Ki, Kd, PID::Direct),
  PID_v2(Kp, Ki, Kd, PID::Direct),
  PID_v2(Kp, Ki, Kd, PID::Direct)
};

void pidSetup() {
  windowStartTime = millis();
  for(int i = 0; i < HEATER_COUNT; ++i) {
    pids[i].SetOutputLimits(0, WINDOW_SIZE);
    pids[i].Start(temperatures[i], 0, targetTemperatures[i]);
  }
}

boolean pidUpdate(int index, int target) {
  if (millis() - windowStartTime > WINDOW_SIZE) {
    windowStartTime += WINDOW_SIZE;
  }
  pids[index].Setpoint(target);
  double output = pids[index].Run(temperatures[index]);
  return (output < millis() - windowStartTime);
}
