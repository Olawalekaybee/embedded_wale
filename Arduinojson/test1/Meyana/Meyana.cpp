#include  "Arduino.h"
#include "Meyana.h"
#include "NewTone.h"
#include "OneWire.h"
#include "DallasTemperature.h"
#include "NewPing.h"
#include "stdarg.h"
#include "Wire.h"
#include "LiquidCrystal_I2C.h"
#include "HX711.h"
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

Pressure::Pressure(const unsigned int n)	{
	n_bioDigester = n;
	balance = new HX711[n];
}

void Pressure::configurePressureProbes(const unsigned int n, ...)	{
	dataPin = new unsigned int[2 * n];
	pressure = new float[n];
	pressurePrev = new float[n];
	sd = new float[n];
	isFirstIteration = new bool[n];
	va_list pinList;
	va_start(pinList, n);
	int j = -1;
	for(int i = 0;i < (2 * n);i++)	{
		j += 1;
		if(i % 2 != 0)	{
			j -= 1;
			continue;
		}
		dataPin[i] = va_arg(pinList, unsigned int);
		dataPin[i + 1] = va_arg(pinList, unsigned int);
		balance[j].begin(dataPin[i], dataPin[i + 1]);
		balance[j].set_gain();
		balance[j].tare(10);
		balance[j].set_scale(1000.0);
		pressure[j] = pressurePrev[j] = sd[j] = 0.0;
		isFirstIteration[j] = true;
	}
	va_end(pinList);
}

void Pressure::readPressures(unsigned int T)	{
	for(int i = 0;i < n_bioDigester;i++)	{
		float mean, mean_of_squares;
		pressurePrev[i] = pressure[i];
		for(int j = 0;j < T;j++)	{
			float val = balance[i].get_units();
			mean = ((j * mean) + val) / float(j + 1);
			mean_of_squares = ((j * mean_of_squares) + sq(val)) / float(j + 1);
		}
		if((fabs(mean - pressure[i]) > (3 * sd[i])) || isFirstIteration[i])	{
			pressure[i] = mean;
		}
		sd[i] = sqrt(mean_of_squares - sq(mean));
	}
}

float Pressure::getPrevPressure(unsigned int i)	{
	return pressurePrev[i];
}

void Pressure::setPrevPressure(unsigned int i, float val)	{
	pressurePrev[i] = val;
}

float Pressure::getPressure(unsigned int i)	{
	return pressure[i];
}

PH::PH(const unsigned int n, ...)	{
	n_bioDigester = n;
	pH = new float[n];
	pHPrev = new float[n];
	sd = new float[n];
	pHPin = new unsigned int[n];
	isFirstIteration = new bool[n];
	va_list pinList;
	va_start(pinList, n);
	for(int i = 0;i < n;i++)	{
		pHPin[i] = va_arg(pinList, unsigned int);
		pH[i] = pHPrev[i] = sd[i] = 0.0;
		isFirstIteration[i] = true;
	}
	va_end(pinList);
	float x[] = {3.725, 3.21, 2.83};
	float y[] = {4.0, 7.0, 9.2};
	for(int i = 0;i < 3;i++)	{
		x_ = ((i * x_) + x[i]) / float(i + 1);
		y_ = ((i * y_) + y [i]) / float(i + 1);
		xy_ = ((i * xy_) +(x[i] * y[i])) / float(i + 1);
		xx_ = ((i * xx_) + (x[i] * x[i])) / float(i + 1);
	}
	m = (xy_ - (x_ * y_)) / (xx_ - (x_ * x_));
	c = ((y_ * xx_) - (x_ * xy_)) / (xx_ - (x_ * x_));
}

float PH::convertPHSignal(float val)	{
	return constrain((m * val) + c, 0.0, 14.0);
}

void PH::readPHValues(unsigned int T)	{
	for(int i = 0;i < n_bioDigester;i++)	{
		float mean, mean_of_squares;
		pHPrev[i] = pH[i];
		for(int j = 0;j < T;j++)	{
			float val = analogRead(pHPin[i]) * 5.0 / 1024.0;
			mean = ((j * mean) + convertPHSignal(val)) / float(j + 1);
			mean_of_squares = ((j * mean_of_squares) + sq(convertPHSignal(val))) / float(j + 1);
		}
		if((fabs(mean - pH[i]) > (3 * sd[i])) || isFirstIteration[i])	{
			pH[i] = mean;
		}
		sd[i] = sqrt(mean_of_squares - sq(mean));
	}
}

float PH::getPrevPH(unsigned int i)	{
	return pHPrev[i];
}

void PH::setPrevPH(unsigned int i, float val)	{
	pHPrev[i] = val;
}

float PH::getPH(unsigned int i)	{
	return pH[i];
}

Level::Level(unsigned int max_depth)	{
	MAX_DEPTH = max_depth;
}

void Level::configureLevelProbes(const unsigned int n, ...) {
	n_bioDigester = n;
	levelProbe = new NewPing[n];
	depth = new float[n];
	depthPrev = new float[n];
	depthLimit = new float[n];
	sd = new float[n];
	isFirstIteration = new bool[n];
	rangeFinder = new RangeFinder[n];

	va_list rFList;
	va_start(rFList, n);
	for(int i = 0;i < n;i++)	{
		rangeFinder[i].arg = new float[3];
		rangeFinder[i].arg = va_arg(rFList, float*);
		levelProbe[i] = NewPing(uint8_t(rangeFinder[i].arg[0]), uint8_t(rangeFinder[i].arg[1]), MAX_DEPTH);
		depthLimit[i] = rangeFinder[i].arg[2];
		depth[i] = depthPrev[i] = sd[i] = 0.0;
		isFirstIteration[i] = true;
	}
	va_end(rFList);
}

void Level::configureBuzzerPins(const unsigned int n, ...) {
	buzzerPin = new unsigned int[n];
	va_list buzzerPinList;
	va_start(buzzerPinList, n);
	for(int i = 0;i < n;i++)	{
		buzzerPin[i] = va_arg(buzzerPinList, unsigned int);
		pinMode(buzzerPin[i], OUTPUT);
		noNewTone(buzzerPin[i]);
	}
	va_end(buzzerPinList);
}

void Level::readLevels(unsigned int T)	{
	for(int i = 0;i < n_bioDigester;i++)	{
		float mean, mean_of_squares;
		depthPrev[i] = depth[i];
		float timeOut = millis() + 5000.0;
		for(int j = 0;j < T;j++)	{
			if(timeOut - millis() <= 0.0) break;
			float val = levelProbe[i].ping_cm();
			mean = ((j * mean) + val) / float(j + 1);
			mean_of_squares = ((j * mean_of_squares) + sq(val)) / float(j + 1);
			delay(round(2 * val * 1e3 / 17150));
		}
		if((fabs(mean - depth[i]) > (3 * sd[i])) || isFirstIteration[i])	{
			depth[i] = mean;
		}
		sd[i] = sqrt(mean_of_squares - sq(mean));
	}
}

float Level::getPrevLevel(unsigned int i)	{
	return depthPrev[i];
}

void Level::setPrevLevel(unsigned int i, float val)	{
	depthPrev[i] = val;
}

float Level::getLevel(unsigned int i)	{
	return depth[i];
}

void Level::updateBuzzers(unsigned long f)	{
	for(int i = 0;i < n_bioDigester;i++)	{
		if(depth[i] > depthLimit[i])	{
			NewTone(buzzerPin[i], f);
		}
		else	{
			noNewTone(buzzerPin[i]);
		}
	}
}

Stirrer::Stirrer(const unsigned int n)	{
	n_bioDigester = n;
}

void Stirrer::configureMotorControls(const unsigned int n, ...)	{
	motor = new Motor[n];

	va_list pinList;
	va_start(pinList, n);
	for(int i = 0;i < n;i++)	{
		motor[i].state = false;
		motor[i].tStart = motor[i].tStop = millis();
		motor[i].pin = new unsigned int[3];

		motor[i].pin[0] = va_arg(pinList, unsigned int);
		pinMode(motor[i].pin[0], INPUT_PULLUP);

		motor[i].pin[1] = va_arg(pinList, unsigned int);
		pinMode(motor[i].pin[1], OUTPUT);
		digitalWrite(motor[i].pin[1], LOW);

		motor[i].pin[2] = va_arg(pinList, unsigned int);
		pinMode(motor[i].pin[2], OUTPUT);
		digitalWrite(motor[i].pin[2], LOW);
	}
	va_end(pinList);
}

void Stirrer::stir(float minute, float hour)	{
	for(int i = 0;i < n_bioDigester;i++)	{
		if(motor[i].state && ((millis() - motor[i].tStart) >= (minute * 60 * 1e3)))	{
			digitalWrite(motor[i].pin[1], LOW);
			motor[i].tStop = millis();
			digitalWrite(motor[i].pin[2], LOW);
			motor[i].state = false;
		}
		if(!motor[i].state && ((millis() - motor[i].tStop) >= ((hour * 60 * 60 * 1e3) - (minute * 60 * 1e3))))	{
			digitalWrite(motor[i].pin[1], HIGH);
			motor[i].tStart = millis();
			digitalWrite(motor[i].pin[2], HIGH);
			motor[i].state = true;
		}
	}
}

Display::Display(const unsigned int n, ...)	{
	n_bioDigester = n;
	screen = new LiquidCrystal_I2C[n];
	va_list addressList;
	va_start(addressList, n);
	for(int i = 0;i < n;i++)	{
		screen[i] = LiquidCrystal_I2C(va_arg(addressList, unsigned int), 20, 4);
	}
	va_end(addressList);
}

void Display::configureDisplays(void)	{
	for(int i = 0;i < n_bioDigester;i++)	{
		screen[i].init();
		screen[i].clear();
		screen[i].home();
		screen[i].backlight();
	}
}

void Display::display(Temperature* t, Pressure* p, PH* pH, Level* l)	{
	for(int i = 0;(i < t->n_bioDigester) && (t != NULL);i++)	{
		if((t->getPrevTemp(i) == t->getTemperature(i)) || (t->getTemperature(i) == DEVICE_DISCONNECTED_C)) {
		if(t->getPrevTemp(i) == t->getTemperature(i)) {
			if(t->isFirstIteration[i])	{
				t->isFirstIteration[i] = false;
			}
			else	{
				continue;
			}
		}
		}
		String d = "Temp = " + String(t->getTemperature(i), 1) + " C";
		while(d.length() < 20)	{
			d += " ";
		}
		screen[i].setCursor(0, 0);
		screen[i].print(d);
	}

	for(int i = 0;(i < p->n_bioDigester) && (p != NULL);i++)	{
		if(p->getPrevPressure(i) == p->getPressure(i)) {
			if(p->isFirstIteration[i])	{
				p->isFirstIteration[i] = false;
			}
			else	{
				continue;
			}
		}
		String d = "Press = " + String(p->getPressure(i), 2) + " Pa";
		while(d.length() < 20)	{
			d += " ";
		}
		screen[i].setCursor(0, 1);
		screen[i].print(d);
	}

	for(int i = 0;(i < pH->n_bioDigester) && (pH != NULL);i++)	{
		if(pH->getPrevPH(i) == pH->getPH(i)) {
			if(pH->isFirstIteration[i])	{
				pH->isFirstIteration[i] = false;
			}
			else	{
				continue;
			}
		}
		String d = "pH = " + String(pH->getPH(i), 1);
		while(d.length() < 20)	{
			d += " ";
		}
		screen[i].setCursor(0, 2);
		screen[i].print(d);
	}

	for(int i = 0;(i < l->n_bioDigester) && (l != NULL);i++)	{
		if(l->getPrevLevel(i) == l->getLevel(i)) {
			if(l->isFirstIteration[i])	{
				l->isFirstIteration[i] = false;
			}
			else	{
				continue;
			}
		}
		String d = "Depth = " + String(l->getLevel(i), 0) + " cm";
		while(d.length() < 20)	{
			d += " ";
		}
		screen[i].setCursor(0, 3);
		screen[i].print(d);
	}
}

Caster::Caster(const unsigned int id)	{
	this->id = id;
}

void Caster::configureCaster(Temperature* t, Pressure* p, PH* pH, Level* l)	{
	this->dataCount = 0;
}

void Caster::cast(Temperature* t, Pressure* p, PH* pH, Level* l, bool mode)	{
    StaticJsonDocument<512> data;
	data["id"] = id;
	data["s"][0] = (t != NULL)? t->n_bioDigester: 0;
	data["s"][1] = (p != NULL)? p->n_bioDigester: 0;
	data["s"][2] = (pH != NULL)? pH->n_bioDigester: 0;
	data["s"][3] = (l != NULL)? l->n_bioDigester: 0;
	for(int i = 0;i < data["s"][0];i++)	{
		data["t"][i] = String(t->getTemperature(i), 2).toFloat();
	}
	for(int i = 0;i < data["s"][1];i++)	{
		data["p"][i] = String(p->getPressure(i), 2).toFloat();
	}
	for(int i = 0;i < data["s"][2];i++)	{
		data["ph"][i] = String(pH->getPH(i), 2).toFloat();
	}
	for(int i = 0;i < data["s"][3];i++)	{
		data["l"][i] = String(l->getLevel(i), 2).toFloat();
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
