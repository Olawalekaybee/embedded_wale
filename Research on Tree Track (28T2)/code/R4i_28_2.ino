#include <SoftwareSerial.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define TRIGPIN 3
#define ECHOPIN 2








SoftwareSerial SIM800(6, 7);  //SIM800L Tx & Rx
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Servo myservo;

bool x = false;
int pos = 0;
float  cMeters;


void ultrasonicSetup() {
  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);
}




void setupOled() {

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.display();

  delay(500);
}


void setup() {

  Serial.begin(9600);
  SIM800.begin(9600);
  myservo.attach(8);
  ultrasonicSetup();
  setupOled();
}


void loop() {


  rotation();
  Serial.println("am running");

  for (unsigned long start = millis(); millis() - start < 5000;) {
    send_Sms(cMeters, 30);
  }
}

void send_Sms(float a, int d) {
  if (a >= d) {

    String gps = "11.837654,10.172917";
    SIM800.println("AT");
    ShowSerialData();

    SIM800.println("AT+CMGF=1");  // Configuring TEXT mode
    ShowSerialData();
    SIM800.println("AT+CMGS=\"+2348144439348\"");
    ShowSerialData();
    String c = "Tree defect,"
               "\n";
    c += "LOCATION: " + String(gps);

    SIM800.print(c);
    ShowSerialData();
    SIM800.write(26);
  } else {
  }
}
void ShowSerialData() {
  while (SIM800.available() > 0)
    Serial.write(SIM800.read());
  delay(500);
}




void rotation() {
  for (pos = 180; pos >= 0; pos--) {
    myservo.write(pos);
    scanning();
    sonar(180 - pos);
  }
  for (pos = 0; pos <= 180; pos++) {
    myservo.write(pos);
    scanning();
    sonar(180 - pos);
  }
}




void scanning() {
  long duration;



  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(5);
  digitalWrite(TRIGPIN, LOW);


  duration = pulseIn(ECHOPIN, HIGH);
  cMeters = microsecondsToCmeters(duration);


  Serial.println("distance is" + String(cMeters) + "cm ");
}




float microsecondsToCmeters(long us) {
  float cm = us / 1000000.0 * 340 * 100 * 0.5;
  return cm;
}






void sonar(int a) {
  double i = 0;
  double j = 0;
  int x = 0;
  int y = 0;
  display.drawCircle(64, 64, 60, 1);
  display.drawCircle(64, 64, 30, 1);
  display.drawLine(64, 64, 22, 22, 1);
  display.drawLine(64, 64, 64, 4, 1);
  display.drawLine(64, 64, 106, 22, 1);
  i = 60 * cos(a * 3.14159 / 180.0);
  j = 60 * sin(a * 3.14159 / 180.0);
  y = (int)j;
  x = (int)i;
  display.drawLine(64, 64, 64 - x, 64 - j, 1);
  //display.drawCircle((64-30*cos(a*3.1416/180.0)), (64+30*cos(a*3.1416/180.0)), 4, 1);
  display.display();
  //delay(50);
  display.clearDisplay();
}
