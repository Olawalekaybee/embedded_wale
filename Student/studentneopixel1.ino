#include <Adafruit_NeoPixel.h>
#define PIN 7

#define NUMPIXELS 16

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 500

void setup() {
  pixels.begin(); // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  pixels.clear();
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL);

  }
}