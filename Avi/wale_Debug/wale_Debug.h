#ifndef wale_Debug_h
#define wale_Debug_h

#include "Arduino.h"

class wale_Debug
{

public:
   bool flag;

    wale_Debug(bool);
    void wale_D(bool, char , float );
};



#endif