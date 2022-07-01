

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif


#define BUTTON_PIN   2

#define PIXEL_PIN    6  

#define PIXEL_COUNT 16  


Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);


boolean oldState = HIGH;
int     mode     = 0;    // Currently-active animation mode, 0-9

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin(); // Initialize NeoPixel strip object 
  strip.show(); 
}

void loop() {

  boolean newState = digitalRead(BUTTON_PIN);

 
  if((newState == LOW) && (oldState == HIGH)) {
   
    delay(20);
    
    newState = digitalRead(BUTTON_PIN);
    if(newState == LOW) {      // set the state to low
      if(++mode > 8) mode = 0; // Move to next mode
      switch(mode) {           // Start the Led animation..
        case 0:
          colorWipe(strip.Color(  0,   0,   0), 50);    // Black/off
          break;
        case 1:
          colorWipe(strip.Color(255,   0,   0), 50);    // Red
          break;
        case 2:
          colorWipe(strip.Color(  0, 255,   0), 50);    // Green
          break;
        case 3:
          colorWipe(strip.Color(  0,   0, 255), 50);    // Blue
          break;
        case 4:
          theaterChase(strip.Color(127, 127, 127), 50); // White
          break;
        case 5:
          theaterChase(strip.Color(127,   0,   0), 50); // Red
          break;
        case 6:
          theaterChase(strip.Color(  0,   0, 127), 50); // Blue
          break;
        case 7:
          rainbow(10);
          break;
        case 8:
          theaterChaseRainbow(50);
          break;
      }
    }
  }

  // Set the last-read button state to the old state.
  oldState = newState;
}


void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}


void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
     
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

  ////~ Dancing rainbow light embedded  with delay within the frame
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0) 
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   set all pixel to zero or low
      for(int c=b; c<strip.numPixels(); c += 3) {
       
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> Red, Green and Blue.
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();               
      delay(wait);                 
      firstPixelHue += 65536 / 90; 
    }
  }
}