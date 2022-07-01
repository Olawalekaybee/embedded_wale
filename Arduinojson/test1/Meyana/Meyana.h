#ifndef Meyana_h
#define Meyana_h

#include  "Arduino.h"
#include "NewTone.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include "NewPing.h"
#include "stdarg.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "HX711.h"
#include "ArduinoJson.h"

class Temperature {
  private:
    OneWire* tempChannel = NULL;
    DallasTemperature* tempProbe = NULL;
    unsigned int* heaterDistribution = NULL;
    float* temp = NULL;
    float* tempPrev = NULL;
    float MIN_TEMP, MAX_TEMP_START;

    typedef struct  {
      unsigned int* pin = NULL;
    } Heater;
    
    Heater* heater = NULL;

  public:
    typedef struct  {
      unsigned int* pin = NULL;
    } Thermostat;

    bool* isFirstIteration = NULL;
    Thermostat* thermostat = NULL;
    volatile float* MAX_TEMP = NULL;
    unsigned int tempInterruptPin, interruptTypePin;
    unsigned int n_bioDigester;
    Temperature(float, float);
    static void pin_ISR(void);
    void configureTempProbes(const unsigned int, ...);
    void configureTempControls(const unsigned int, ...);
    void setHeaterDistribution(const unsigned int, ...);
    void configureHeaterPins(const unsigned int, ...);
    void readTemperatures(void);
    float getPrevTemp(unsigned int);
    void setPrevTemp(unsigned int, float);
    float getTemperature(unsigned int);
    void updateHeaters(void);
};

class Pressure  {
  private:
    HX711* balance = NULL;
    unsigned int* dataPin = NULL;
    float* pressure = NULL;
    float* pressurePrev = NULL;
    float* sd = NULL;

  public:
    bool* isFirstIteration = NULL;
    unsigned int n_bioDigester;
    Pressure(const unsigned int);
    void configurePressureProbes(const unsigned int, ...);
    void readPressures(unsigned int);
    float getPrevPressure(unsigned int);
    void setPrevPressure(unsigned int, float);
    float getPressure(unsigned int);
};

class PH  {
  private:
    float* pH = NULL;
    float* pHPrev = NULL;
    float* sd = NULL;
    unsigned int* pHPin = NULL;
    float m, c, x_, y_, xy_, xx_;
    float convertPHSignal(float);

  public:
    bool* isFirstIteration = NULL;
    unsigned int n_bioDigester;
    PH(const unsigned int, ...);
    void readPHValues(unsigned int);
    float getPrevPH(unsigned int);
    void setPrevPH(unsigned int, float);
    float getPH(unsigned int);
};

class Level {
  private:
    NewPing* levelProbe = NULL;
    float* depth = NULL;
    float* depthPrev = NULL;
    float* sd = NULL;

    typedef struct  {
      float* arg = NULL;
    } RangeFinder;
    
    RangeFinder* rangeFinder = NULL;
    unsigned int* buzzerPin = NULL;

    unsigned int MAX_DEPTH;
    float* depthLimit = NULL;

  public:
    bool* isFirstIteration = NULL;
    unsigned int n_bioDigester;
    Level(unsigned int);
    void configureLevelProbes(const unsigned int, ...);
    void configureBuzzerPins(const unsigned int, ...);
    void readLevels(unsigned int);
    float getPrevLevel(unsigned int);
    void setPrevLevel(unsigned int, float);
    float getLevel(unsigned int);
    void updateBuzzers(unsigned long);
};

class Stirrer {
  public:
    typedef struct  {
      bool state;
      double tStart, tStop;
      unsigned int* pin = NULL;
    } Motor;

    Motor* motor = NULL;
    unsigned int n_bioDigester;
    Stirrer(const unsigned int);
    void configureMotorControls(const unsigned int, ...);
    void stir(float, float);
};

class Display {
  private:
    LiquidCrystal_I2C* screen = NULL;

    unsigned int n_bioDigester;

  public:
    Display(const unsigned int, ...);
    void configureDisplays(void);
    void display(Temperature* t = NULL, Pressure* p = NULL, PH* pH = NULL, Level* l = NULL);
};

class Caster  {
  private:
    int id;
    unsigned long dataCount;

  public:
    Caster(const unsigned int);
    void configureCaster(Temperature* t = NULL, Pressure* p = NULL, PH* pH = NULL, Level* l = NULL);
    void resetNode(const unsigned int);
    void cast(Temperature* t = NULL, Pressure* p = NULL, PH* pH = NULL, Level* l = NULL, bool mode = false);
};

#endif