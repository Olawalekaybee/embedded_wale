#include ".h"
#include "String.h"
#include "Arduino.h"
#include "TinyGPS++.h"
#include "SoftwareSerial.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include "dht.h"
#include "stdarg.h"
#include "Adafruit_INA219.h"
#include "Wire.h"

// #include "ArduinoJson.h"
Adafruit_INA219 ina219;


TinyGPSPlus gps;
dht DHT;
SoftwareSerial gpsSerial(2, 3); // green 3 // yellow 2  

Temperature::Temperature(float min)
{
    MIN_TEMP = min;
}

void Temperature::configureTempProbes(const unsigned int n, ...)
{
    team15 = n;
    tempChannel = new OneWire[n];
    tempProbe = new DallasTemperature[n];
    temp = new float[n];
    isFirstIteration = new bool[n];

    va_list tempPins;
    va_start(tempPins, n);
    for (int i = 0; i < n; i++)
    {
        tempChannel[i] = OneWire(va_arg(tempPins, unsigned int));
        tempProbe[i] = DallasTemperature(&tempChannel[i]);
        tempProbe[i].begin();
        isFirstIteration[i] = true;
    }
    va_end(tempPins);
}

void Temperature::readTemperatures(void)
{
    for (int i = 0; i < team15; i++)
    {

        tempProbe[i].requestTemperatures();
        temp[i] = tempProbe[i].getTempCByIndex(0);
        temp[i] = (temp[i] == DEVICE_DISCONNECTED_C) ? -127 : temp[i];
    }
}

float Temperature::getTemperature(unsigned int i)
{
    return temp[i];
}

Dh::Dh(float min)
{
    MIN_ht = min;
}

void Dh::configuredh(const unsigned int n, ...)
{

    team15 = n;
    t = new float[n];
    h = new float[n];

    va_list dhPins;
    va_start(dhPins, n);
    for (int i = 0; i < n; i++)
    {

        dhChannel = va_arg(dhPins, unsigned int);
        pinMode(dhChannel, INPUT_PULLUP);
    }
    va_end(dhPins);
}

void Dh::readDh(void)
{
    for (int i = 0; i < team15; i++)
    {

        int t_val = DHT.read22(dhChannel);
        t[i] = DHT.temperature;
        h[i] = DHT.humidity;
    }
}

float Dh::getH(unsigned int i)
{
    return h[i];
}

float Dh::getT(unsigned int i)
{
    return t[i];
}

Location::Location(const unsigned int n)
{
    team15 = n;

    lat = new float[n];
    lon = new float[n];
}

void Location::configureLocation(const unsigned int x)
{
    gpsSerial.begin(x);
}

void Location::readLocation(unsigned int q)
{
    boolean newData = false;
    for (unsigned long start = millis(); millis() - start < q;)
    {
        while ((gpsSerial.available() > 0))
        {
            if (gps.encode(gpsSerial.read()))
            {
                newData = true;
                break;
            }
        }
    }
    for (int i = 0; i < team15; i++)
    {
        if (newData)
        {

            lat[i] = gps.location.lat();
            lon[i] = gps.location.lng();
            month = gps.date.month();
            day = gps.date.day();
            year = gps.date.year();
            hr = gps.time.hour();
            min = gps.time.minute();

            date = String(month) + "/" + String(day) + "/" + String(year);
            time = String(hr + 1) + ":" + String(min);
            newData = false;
        }
        else
        {

            lat[i] = 0;
            lon[i] = 0;
        }
    }
}

String Location::getLat(unsigned int i)
{
    return (String(lat[i], 6)); //  return (String(lon[i], 6)); 
}

String Location::getLon(unsigned int i)
{
    return (String(lon[i], 6)); 
}

String Location::getTime()
{
    return time;
}

String Location::getdate()
{
    return date;
}

Current::Current(unsigned int v)
{
    max = v;
}

void Current::configureCV(const unsigned int n, ...)
{
    team15 = n;
    Signal_V = new int[n];
    Signal_c = new double[n];
    rawdata = new int[n];

    va_list cvPins;
    va_start(cvPins, n);
    for (int i = 0; i < n; i++)
    {

        cvChannel = va_arg(cvPins, unsigned int);
        //   pinMode(cvChannel, INPUT_PULLUP);
    }
    va_end(cvPins);
}

void Current::readCV(int neutralize, int susceptibility)
{
    for (int i = 0; i < team15; i++)
    {
        rawdata[i] = analogRead(cvChannel);
        Signal_V[i] = (rawdata[i] / 1024.0) * 5000;
        Signal_c[i] = ((Signal_V[i] - neutralize) / susceptibility);
        // Serial.println(rawdata[i]);
    }
}

float Current::get_mA(unsigned int i)
{
    return (Signal_c[i]);
}

float Current::get_mV(unsigned int i)
{
    return (Signal_V[i]);
}

Bi_directional::Bi_directional(unsigned int n)
{
    // mA = v;
    shuntvoltage = new float[n];
    busvoltage = new float[n];
    current_mA = new float[n];
    loadvoltage = new float[n];
    power_mW = new float[n];
    team15 = n;
}

void Bi_directional::Set_Bidirectional()
{
    ina219.begin();
    Wire.begin();
    ina219.setCalibration_16V_400mA(); //setCalibration_32V_1A();
}
void Bi_directional::read_Bidirectional(int x)
{
    float shv = 0.0;
    float bsv = 0.0;
    float ca = 0.0;
    float po = 0.0;

    for (int i = 0; i < team15; i++)
    {
        for (int j = 0; j < x; j++)
        {
            shv += ina219.getShuntVoltage_mV();
            bsv += ina219.getBusVoltage_V();
            ca += ina219.getCurrent_mA();
            loadvoltage[i] = busvoltage[i] + (shuntvoltage[i] / 1000);
            po += ina219.getPower_mW();
        }
        shuntvoltage[i] = shv / x;
        busvoltage[i] = bsv / x;
        current_mA[i] = ca / x;

        power_mW[i] = po / x;

        loadvoltage[i] = (busvoltage[i]) + (shuntvoltage[i] / 1000);
    }
}

float Bi_directional::get_shuntvolage(unsigned int i)
{
    return (loadvoltage[i]   * 35); // shuntvoltage[i] 
}
float Bi_directional::get_busvoltage(unsigned int i)
{
    return (busvoltage[i]);
}
float Bi_directional::get_current_mA(unsigned int i)
{
    return (current_mA[i]);
}
float Bi_directional::get_power_mW(unsigned int i)
{
    return (power_mW[i]);
}
float Bi_directional::get_loadvoltage(unsigned int i)
{
    return (loadvoltage[i]);
}
