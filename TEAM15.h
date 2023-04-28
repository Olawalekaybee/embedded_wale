#ifndef TEAM15_h
#define TEAM15_h

#include "Arduino.h"

#include "OneWire.h"
#include "DallasTemperature.h"
#include "dht.h"
#include "stdarg.h"

#include "Adafruit_INA219.h"


class Temperature
{
private:
  OneWire *tempChannel = NULL;
  DallasTemperature *tempProbe = NULL;

  float MIN_TEMP;

public:
  bool *isFirstIteration = NULL;
  float *temp = NULL;
  unsigned int team15;
  Temperature(float);
  void configureTempProbes(const unsigned int, ...);
  void readTemperatures(void);
  float getTemperature(unsigned int);
};

class Dh
{
private:
  float MIN_ht;

  unsigned int dhChannel;

public:
  unsigned int team15;
  float *t = NULL;
  float *h = NULL;
  Dh(float);
  void configuredh(const unsigned int, ...);
  void readDh(void);
  float getH(unsigned int);
  float getT(unsigned int);
};

class Location
{
private:
  unsigned int team15;

public:
  float *lat = NULL;
  float *lon = NULL;
  int month, day, year, hr, min;

  String date, time;

  Location(const unsigned int);
  void configureLocation(const unsigned int);
  void readLocation(unsigned int);
  String getLat(unsigned int);
  String getLon(unsigned int);
  String getTime();
  String getdate();
};

class Current
{
private:
  unsigned int cvChannel;
  unsigned int max;

public:
  int susceptibility, neutralize;
  unsigned int team15;
  int *Signal_V = NULL;
  double *Signal_c = NULL;
  int *rawdata = NULL;
  Current(unsigned int);
  void configureCV(const unsigned int, ...);
  void readCV(int, int);
  float get_mA(unsigned int);
  float get_mV(unsigned int);
};

class Bi_directional
{
private:
  float *shuntvoltage = NULL;
  float *busvoltage = NULL;
  float *current_mA = NULL;
  float *loadvoltage = NULL;
  float *power_mW = NULL;

public:
  Bi_directional(unsigned int);
  unsigned int team15;
  void Set_Bidirectional();
  void read_Bidirectional(int);
  float get_shuntvolage(unsigned int);
  float get_busvoltage(unsigned int);
  float get_current_mA(unsigned int);
  float get_power_mW(unsigned int);
  float get_loadvoltage(unsigned int);
};

// class Caster
// {
// private:
//   int id;
//   unsigned long dataCount;

// public:
//   Caster(const unsigned int);
//   void configureCaster(Temperature *t = NULL, Dh *d = NULL, Location *l = NULL, Current *i = NULL);
//   void cast(Temperature *t = NULL, Dh *d = NULL, Location *l = NULL, Current *i = NULL, bool mode = false);
// };

#endif