#ifndef Meyana2_h
#define Meyana2_h

#include "Arduino.h"

#include "OneWire.h"
#include "DallasTemperature.h"

#include "stdarg.h"
#include "Wire.h"
#include "ArduinoJson.h"

class Temperature
{
private:
    OneWire *tempChannel = NULL;
    DallasTemperature *tempProbe = NULL;
    unsigned int *heaterDistribution = NULL;
    float *temp = NULL;
    float *tempPrev = NULL;
    float MIN_TEMP, MAX_TEMP_START;

    typedef struct
    {
        unsigned int *pin = NULL;
    } Heater;

    Heater *heater = NULL;

public:
    typedef struct
    {
        unsigned int *pin = NULL;
    } Thermostat;
    
    Thermostat *thermostat = NULL;
    bool *isFirstIteration = NULL;
   
    volatile float *MAX_TEMP = NULL;
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

class Caster
{
private:
    int id;
    unsigned long dataCount;

public:
    Caster(const unsigned int);
    void configureCaster(Temperature *t = NULL);
    void resetNode(const unsigned int);
    void cast(Temperature *t = NULL, bool mode = false);
};

#endif