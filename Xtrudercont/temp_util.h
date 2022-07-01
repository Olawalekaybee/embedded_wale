#include "max6675.h"

MAX6675 thermocouples[] = {
  MAX6675(43, 44, 45), // heater 1 temperature
  MAX6675(39, 40, 41), // heater 2 temperature
  MAX6675(35, 36, 37), // heater 3 temperature
  MAX6675(31, 32, 33)  // extruder temperature
};

int readTemp(int index) {
  return thermocouples[index].readCelsius();
}
