
#include "Arduino.h"
#include "Wheelchair.h"
#include "stdarg.h"
#include "ArduinoJson.h"

WC::WC(const unsigned int n)
{
    n_chair = n;
    js = new int[n];
    x = new int[n];
    y = new int[n];
    // state[i] = new int[n]
}

void WC::configureJs(const unsigned int n, ...)
{
    pawa = new int[n];
    steeringPawa = new int[n];
    dir = new bool[n];
    steeringDir = new bool[n];
    state = new int[n];
    jsPin = new unsigned int[2 * n];

    isFirstIteration = new bool[n];

    va_list pinList;
    va_start(pinList, n);
    int j = -1;
    for (int i = 0; i < (3 * n); i++)
    {
        j += 1;
        if (i % 3 != 0)
        {
            j -= 1;
            continue;
        }
        jsPin[i] = va_arg(pinList, unsigned int);
        pinMode(jsPin[i], INPUT_PULLUP);
        jsPin[i + 1] = va_arg(pinList, unsigned int);
        pinMode(jsPin[i + 1], INPUT_PULLUP);
        jsPin[i + 2] = va_arg(pinList, unsigned int);
        pinMode(jsPin[i + 2], INPUT_PULLUP);

        isFirstIteration[j] = true;
    }
    va_end(pinList);
}

void WC::readJs(void)
{
    for (int i = 0; i < n_chair; 1 ++)
    {
        x[i] = analogRead(jsPin[i]);
        y[i] = analogRead(jsPin[i + 1]);
        state[i] = analogRead(jsPin[i + 2]);
        pawa[i] = abs(analogRead(jsPin[i + 1]) - y[i]) / 2;
        dir[i] = (analogRead(jsPin[i + 1]) > y[i]);
        steeringPawa[i] = abs(analogRead((jsPin[i])) - xBase) / 2;
        steeringDir[i] = (analogRead((jsPin[i])) > xBase);
    }
}

void WC::setDrvdistributon(const unsigned int n, ...)
{
    drvDistribution = new unsigned int[n];

    va_list DDistList;
    va_start(DDistList, n);
    for (int i = 0; i < n; i++)
    {
        drvDistribution[i] = va_arg(DDistList, unsigned int);
        drv[i].pin = new unsigned int[drvDistribution[i]];
    }
    va_end(DDistList);
}

void WC::configureDriverMPins(const unsigned int n, ...)
{
    va_list DrvList;
    va_start(DrvList, n);
    for (int i = 0; i < n; i++)
    {
        drv[i].pin = va_arg(DrvList, unsigned int *);
        for (int j = 0; j < drvDistribution[i]; j++)
        {
            pinMode(drv[i].pin[j], OUTPUT);
            digitalWrite(drv[i].pin[j], LOW);
        }
    }
    va_end(DrvList);
}

void WC::updateDriverM(void)
{
    for (int i = 0; i < n_chair; i++)
    {

        if (pawa[i] > 20)
        {
            if (steeringPawa[i] < 20)
            {
                if (dir[i])
                { // forward
                    forward(pawa[i], pawa[i]);
                }
                else
                { // backward
                    backward(pawa[i], pawa[i]);
                }
            }
            else
            {
                if (dir[i])
                {
                    if (steeringDir[i])
                    { // forward right
                        forward(constrain(pawa[i] - steeringPawa[i], 0, pawa[i]), pawa[i]);
                    }
                    else
                    { // forward left
                        forward(pawa[i], constrain(pawa[i] - steeringPawa[i], 0, pawa[i]));
                    }
                }
                else
                {
                    if (steeringDir[i])
                    { // backward right
                        backward(pawa[i] - steeringPawa[i], pawa[i]);
                    }
                    else
                    { // backward left
                        backward(pawa[i], pawa[i] - steeringPawa[i]);
                    }
                }
            }
        }
        else if (steeringPawa[i] > 20)
        {
            if (steeringDir[i])
            { // right
                right(steeringPawa[i]);
            }
            else
            { // left
                left(steeringPawa[i]);
            }
        }
        else
        {
            stopp();
        }
    }
}

void WC::forward(int speed1, int speed2)
{
    //  Serial.println("forward");
    drive(true, true, speed1, speed2);
}

void WC::backward(int speed1, int speed2)
{
    //  Serial.println("backward");
    drive(false, false, speed1, speed2);
}

void WC::right(int speed)
{
    //  Serial.println("right");
    drive(false, true, speed, speed);
}

void WC::left(int speed)
{
    //  Serial.println("left");
    drive(true, false, speed, speed);
}

void drive(bool dir1, bool dir2, int speed1, int speed2)
{

    for (int i = 0; i < n_chair; i++)
    {
        for (int j = 0; (j < drvDistribution[i]); j++)
        {
            if (drvDistribution[i] > 0)
            {
                if (dir1[i])
                {
                    digitalWrite(drv[i].pin[0], LOW);
                    analogWrite(drv[i].pin[0], speed1);
                }
                else
                {
                    digitalWrite(drv[i].pin[0], HIGH);
                    analogWrite(drv[i].pin[1], 255 - speed1);
                }
                yield();
                if (dir[i])
                {
                    analogWrite(drv[i].pin[2], 255 - speed2);
                    digitalWrite(drv[i].pin[3], HIGH);
                }
                else
                {
                    analogWrite(drv[i].pin[2], speed2);
                    digitalWrite(drv[i].pin[3], LOW);
                }
            }
            // else
            // {
            //     digitalWrite(drv[i].pin[j]) ? HIGH : LOW);
            // }
        }

        speed1 = constrain(speed1, 0, 255);
        speed2 = constrain(speed2, 0, 255);
        Serial.print(dir1[i] ? "" : "-");
        Serial.print(speed1);
        Serial.print(dir2[i] ? "\t" : "\t-");
        Serial.print(speed2);
        Serial.println();
    }
}