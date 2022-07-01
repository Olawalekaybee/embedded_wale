
#include "wale_Debug.h"
#include "Arduino.h"

wale_Debug::wale_Debug(bool x)
{
    flag = x;
}

void wale_Debug::wale_D(bool c,char y, float z ) 
{
    if((flag)&&(c==true)){
        #define debug(y) Serial.print(y)
        #define debugln(z) Serial.println(y)
    }
    else {
        #define debug(y)
        #define debugln(z)
    }
}