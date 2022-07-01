#define Pin 7

void setup() {
  pinMode(Pin, OUTPUT);
  Serial.begin(115200);

}

void loop() {
 digitalWrite(Pin, HIGH);
 Serial.println(Pin);
}
