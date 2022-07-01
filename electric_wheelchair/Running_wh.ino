#include<Wheelchair.h>

WC w(1);

void setup()    {
  Serial.begin(115200);
  w.configureJs(1, A0, A1, 8);

//  w.setDrvdistributon(1, 2);
  unsigned int h[] = {4, 5, 6, 7};
  w.configureDriverMPins(1, h);


}

void loop () {
  blnk();
  w.readJs();
  w.updateDriverM();

}


void blnk(){
  Serial.println("checkkk ");
  delay(500); 
  Serial.println("checkkk ");
  }