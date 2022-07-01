#include <wale_Debug.h>

#define test 9
wale_Debug w(false, 0);
void setup() {
  Serial.begin(115200);
  pinMode(test, OUTPUT);

}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(test, HIGH);
  w.wale_D(0, "value1:\t", (digitalRead(test)), 200);
  digitalWrite(test, LOW);
  w.wale_D(0, "value2:\t", (digitalRead(test)), 1000);
}
