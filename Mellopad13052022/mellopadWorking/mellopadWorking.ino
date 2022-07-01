
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_NeoPixel.h>

#define NUMPIXELS 16
#define ONE_WIRE_BUS 7
#define PIN 3
#define DELAYVAL 10
#define control 12

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature Mellopad_T(&oneWire);
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int  buttonPin = 5;
const int btPin = 2;

const int vm_Pin1 = 6;
const int heater_Pin1 = 9;

int counter = 1;
int counterT = 1;
int buttonState = 0;
int BTState = 0;
int lastButtonState = 0;
int lastBTState = 0;
float tempC;
bool flag1 = false;
bool flag2 = false;
void setup(void)
{
  pixels.begin();
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(heater_Pin1, OUTPUT);
  //pinMode(control, OUTPUT);

  pinMode(btPin, INPUT_PULLUP);
  pinMode(vm_Pin1, OUTPUT);

  Serial.begin(115200);
  Mellopad_T.begin();
  digitalWrite(vm_Pin1, HIGH);
  delay(200);
  digitalWrite(vm_Pin1, LOW);

}

void loop(void) {

  mellopad_Th(40.0, 50.0);
  Vm(10000, 2000); // on off
  // ConTr ();
}



void mellopad_Th(float Min, float Max) {
  //digitalWrite(control, HIGH);
  Mellopad_T.requestTemperatures();
  tempC = Mellopad_T.getTempCByIndex(0);

  Serial.print("Celsius temperature: \n");
  Serial.println(tempC);

  if ((((tempC)  <= ((((Min + Max) / 2)) + 2)))) {
    //    digitalWrite(heater_Pin1, HIGH);
    //    Neomellopad1();
    flag1 = true;
  } else {
    flag1 = false;
//    digitalWrite(heater_Pin1, LOW);
//    Neomellopad2();
  }

  BTState = digitalRead(btPin);

  if (BTState != lastBTState) {

    if (BTState == HIGH) {
      counterT++;
    }
    delay(10);
  }
  lastBTState = BTState;
  if (flag1 == true) {
    digitalWrite(heater_Pin1, HIGH);
    Neomellopad1();
    if ((counterT % 2 == 0)) {
      if (((tempC)  <= (Min)) && ((flag1 == true))) {
        digitalWrite(heater_Pin1, HIGH);
        Serial.println(heater_Pin1);
        //Serial.println("ONcounter");
        Neomellopad1();
      }
      else {
        digitalWrite(heater_Pin1, LOW);
        Neomellopad2();
      }
    }
  } else {
    digitalWrite(heater_Pin1, LOW);
    Neomellopad2();
  }
}


void Vm(float Timer, float minTimer) {
  
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {

    if (buttonState == HIGH) {

      counter++;
      //Serial.println(counter);
    }
    delay(10);
  }
  lastButtonState = buttonState;

  if (counter % 2 == 0) {
    digitalWrite(vm_Pin1, HIGH);

  } else {
    digitalWrite(vm_Pin1, LOW);

  }

}

void Neomellopad1() {
  pixels.setPixelColor(0, pixels.Color(0, 0, 139));// red  off
  pixels.show();
}

void Neomellopad2() {
  pixels.setPixelColor(0, pixels.Color(139, 0, 0));//blueon < max
  pixels.show();
}

void Neomellopad3() {
  pixels.setPixelColor(0, pixels.Color(0, 100, 0)); //green  on < min
  pixels.show();
}