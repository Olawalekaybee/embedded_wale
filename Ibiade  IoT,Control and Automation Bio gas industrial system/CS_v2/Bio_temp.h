#include <OneWire.h>
#include <DallasTemperature.h>
#include <Array.h>

#define Min_T 30

#define Max_T 45

#define counter 1
#define bio_T_wire 7
#define heater_T_wire 8

int deviceCount[counter + 1] = {
  0,
  0
};
Array<float, 2> temp;
Array<float, 3> Htemp;

OneWire oneWire(bio_T_wire);
OneWire oneWire_H(heater_T_wire);
DallasTemperature bioT(&oneWire);
DallasTemperature heater_T(&oneWire_H);

void config_T() {

  bioT.begin();
  heater_T.begin();
}

void bio_Temperature() {
  deviceCount[0] = bioT.getDeviceCount();
  bioT.requestTemperatures();
  for (int i = 0; i < deviceCount[0]; i++) {
    temp[i] = bioT.getTempCByIndex(i);
    temp[i] = (temp[i] == DEVICE_DISCONNECTED_C) ? -1 : temp[i];
  }

}

void heater_Temperature() {
  deviceCount[1] = heater_T.getDeviceCount();
  heater_T.requestTemperatures();
  for (int i = 0; i < deviceCount[1]; i++) {
    Htemp[i] = heater_T.getTempCByIndex(i);
    Htemp[i] = (Htemp[i] == DEVICE_DISCONNECTED_C) ? -1 : Htemp[i];
  }

 
}

// float mean(int x)
// {
//   float avgTemp;

//   avgTemp = (x > 1) ? ((temp[0] + temp[1]) / 2) : (x == 1) ? ((temp[0]))
//                                                            : -1;

//   return avgTemp;
// }
// float mean0(int x)
// {
//   float avgTemp2;

//   avgTemp2 = (x == 4) ? ((temp[2] + temp[3]) / 2) : (x == 3) ? ((temp[2]))
//                                                              : -1;

//   return avgTemp2;
// }