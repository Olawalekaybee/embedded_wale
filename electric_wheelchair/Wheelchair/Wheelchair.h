#ifndef Wheelchair_h
#define Wheelchair_h

#include "Arduino.h"
#include "stdarg.h"
#include "ArduinoJson.h"

class WC
{
private:
    int* js = NULL;
    unsigned int* jsPin = NULL;
    unsigned int* drvDistribution = NULL;
    int* pawa = NULL;
    bool* dir = NULL;
    int* steeringPawa = NULL;
    bool* steeringDir = NULL;

    typedef struct
    {
        unsigned int *pin = NULL;
    } Drv;

    Drv* drv = NULL;

public:
    int* x = NULL;
    int* y = NULL;

    int* state = NULL;
    bool* isFirstIteration = NULL;
    unsigned int n_chair;
    WC(const unsigned int);
    void configureJs(const unsigned int, ...);
    readJs(void);
    void configureDriverMPins();
    
    void setDrvdistributon(const unsigned int n, ...);
    void updateDriverM(const unsigned int n, ...);
    void forward(int , int);
    void backward(int , int);
    void right(int );
    void left(int );
    void drive(unsigned int, bool, bool, int, int);
};



class Caster
{
private:
    int id;
    unsigned long dataCount;

public:
    Caster(const unsigned int);
    void configureCaster(Temperature *t = NULL, Pressure *p = NULL, PH *pH = NULL, Level *l = NULL);
    void resetNode(const unsigned int);
    void cast(Temperature *t = NULL, Pressure *p = NULL, PH *pH = NULL, Level *l = NULL, bool mode = false);
};

#endif