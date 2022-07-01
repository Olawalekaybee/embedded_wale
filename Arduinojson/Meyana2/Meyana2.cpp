#include  "Arduino.h"
#include "Meyana2.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include "stdarg.h"
#include "Wire.h"

#include "ArduinoJson.h"

Temperature::Temperature(float min, float max)	{
	MIN_TEMP = min;
	MAX_TEMP_START = max;
}

void Temperature::configureTempProbes(const unsigned int n, ...) {
	n_bioDigester = n;
	tempChannel = new OneWire[n];
	tempProbe = new DallasTemperature[n];
	temp = new float[n];
	tempPrev = new float[n];
	isFirstIteration = new bool[n];
	heater = new Heater[n];
	MAX_TEMP = new volatile float[n];

	va_list tempPins;
	va_start(tempPins, n);
	for(int i = 0;i < n;i++)	{
		tempChannel[i] = OneWire(va_arg(tempPins, unsigned int));
		tempProbe[i] = DallasTemperature(&tempChannel[i]);
		tempProbe[i].begin();
		tempPrev[i] = DEVICE_DISCONNECTED_C;
		MAX_TEMP[i] = MAX_TEMP_START;
		isFirstIteration[i] = true;
	}
	va_end(tempPins);
}

void Temperature::configureTempControls(const unsigned int n, ...)	{
	thermostat = new Thermostat[n];

	va_list pinList;
	va_start(pinList, n);
	for(int i = 0;i < n;i++)	{
		thermostat[i].pin = new unsigned int[2];

		thermostat[i].pin[0] = va_arg(pinList, unsigned int);
		pinMode(thermostat[i].pin[0], INPUT_PULLUP);

		thermostat[i].pin[1] = va_arg(pinList, unsigned int);
		pinMode(thermostat[i].pin[1], INPUT_PULLUP);
	}
	va_end(pinList);
}

void Temperature::setHeaterDistribution(const unsigned int n, ...) {
	heaterDistribution = new unsigned int[n];

	va_list hDistList;
	va_start(hDistList, n);
	for(int i = 0;i < n;i++)	{
		heaterDistribution[i] = va_arg(hDistList, unsigned int);
		heater[i].pin = new unsigned int[heaterDistribution[i]];
	}
	va_end(hDistList);
}

void Temperature::configureHeaterPins(const unsigned int n, ...) {
	va_list heaterList;
	va_start(heaterList, n);
	for(int i = 0;i < n;i++)	{
		heater[i].pin = va_arg(heaterList, unsigned int*);
		for(int j = 0;j < heaterDistribution[i];j++)	{
			pinMode(heater[i].pin[j], OUTPUT);
    		digitalWrite(heater[i].pin[j], LOW);
		}
	}
	va_end(heaterList);
}

void Temperature::readTemperatures(void)	{
	for(int i = 0;i < n_bioDigester;i++)	{
		tempProbe[i].requestTemperatures();
		temp[i] = tempProbe[i].getTempCByIndex(0);
		temp[i] = (temp[i] == DEVICE_DISCONNECTED_C)? tempPrev[i]: temp[i];
	}
}

float Temperature::getPrevTemp(unsigned int i)	{
	return tempPrev[i];
}

void Temperature::setPrevTemp(unsigned int i, float val)	{
	tempPrev[i] = val;
}

float Temperature::getTemperature(unsigned int i)	{
	return temp[i];
}

void Temperature::updateHeaters(void)	{
	for(int i = 0;i < n_bioDigester;i++)	{
		for(int j = 0;(j < heaterDistribution[i]) && (temp[i] != DEVICE_DISCONNECTED_C);j++)	{
			if(heaterDistribution[i] > 1)	{
				digitalWrite(heater[i].pin[j], (temp[i] <= (MIN_TEMP + (j * (MAX_TEMP[i] - MIN_TEMP) / heaterDistribution[i]))) ? HIGH : LOW);
			}
			else	{
				digitalWrite(heater[i].pin[j], (temp[i] <= (MIN_TEMP + ((MAX_TEMP[i] - MIN_TEMP) / 2))) ? HIGH : LOW);
			}
		}
	}
}


Caster::Caster(const unsigned int id)	{
	this->id = id;
}

void Caster::configureCaster(Temperature* t)	{
	this->dataCount = 0;
}

void Caster::cast(Temperature* t, bool mode)	{
    StaticJsonDocument<512> data;
	data["id"] = id;
	data["s"][0] = (t != NULL)? t->n_bioDigester: 0;
	
	for(int i = 0;i < data["s"][0];i++)	{
		data["t"][i] = String(t->getTemperature(i), 2).toFloat();
	}

	if(Serial.available() > 0)	{
		while(Serial.available() > 0)	int p = Serial.read();
		if(!mode)	{
			serializeJson(data, Serial);
		}
		else	{
			Serial.print("\nData(" + String(dataCount) + ") : ");
			serializeJson(data, Serial);
			dataCount += 1;
		}
	}
	else if(mode)	{
		Serial.print("\nData(" + String(dataCount) + ") : ");
		serializeJson(data, Serial);
		dataCount += 1;
	}
}
