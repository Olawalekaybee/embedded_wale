/*
  API KEYS FOR EACH CPS @ TEST POST:

  /// 5ZPBMJGQ3S2N7XXK ----> vp 2'//// 
  /// TSSPEJ9C1EYUNSH9 ----> vp 3////
  /// H03B7KMEYRH1N00I ----> vp 1////
  /// FSHQHRIUH2UDFWDB ----> vp 4////
*/






#include <TEAM15.h>
#include <MAX471.h>
#include <SoftwareSerial.h>
#define MIN_T 30.0


float mA_value = 0.0;
float mV_value = 0.0;
float interferance_value = 0.0;

#define rxPin 6  // 8
#define txPin 8  // 6
#define TEST_DELAY delay(2000);
#define VT_PIN A4  //A0
#define AT_PIN A5  //A1




Temperature t(MIN_T);
Dh dh(MIN_T);
Location l(1);

MAX471 myMax471(ADC_10_bit, VCC_BAT, AT_PIN, VT_PIN);
SoftwareSerial SIM800(rxPin, txPin);

void setup() {
  Serial.begin(9600);
  SIM800.begin(9600);


  t.configureTempProbes(1, 7);
  l.configureLocation(9600);
  dh.configuredh(1, 9);


  delay(1000);
}

void loop() {

  Max471_read(10);
  t.readTemperatures();
  dh.readDh();
  l.readLocation(2000);
  send_cloud();

  delay(1000);
}



void Max471_read(int x) {
  float I = 0.0;
  float V = 0.0;
  for (int i = 0; i < x; i++) {
    I += myMax471.CurrentRead() * 1000 / x;
    V += myMax471.VoltageRead() * 1000 / x;
  }
  mA_value = I;
  mV_value = V;


  float c = 0.0;
  for (unsigned long start = millis(); millis() - start < 300;) {
    c = myMax471.VoltageRead() * 1000;

    for (unsigned long start = millis(); millis() - start < 1000;) {
      interferance_value = abs(((c < mV_value) || (c > mV_value)) ? (mV_value - c) : (c - mV_value));
      Serial.println("interferance_value(mV) :" + String(interferance_value, 2));
    }
  }
}

void send_cloud() {

  for (unsigned long start = millis(); millis() - start < 3000;) {
    if (SIM800.available() > 0)
      Serial.write(SIM800.read());

    SIM800.println("AT");
    delay(1000);

    SIM800.println("AT+CPIN?");
    delay(1000);

    SIM800.println("AT+CREG?");
    delay(1000);

    SIM800.println("AT+CGATT?");
    delay(1000);

    SIM800.println("AT+CIPSHUT");
    delay(1000);

    SIM800.println("AT+CIPSTATUS");
    delay(2000);

    SIM800.println("AT+CIPMUX=0");
    delay(2000);

    ShowSerialData();

    SIM800.println("AT+CSTT=\"web.gprs.mtnnigeria.net\"");  //start task and setting the APN,

    delay(1000);

    ShowSerialData();

    SIM800.println("AT+CIICR");  //bring up wireless connection
    delay(3000);

    ShowSerialData();

    SIM800.println("AT+CIFSR");  //get local IP adress
    delay(2000);

    ShowSerialData();

    SIM800.println("AT+CIPSPRT=0");
    delay(3000);

    ShowSerialData();

    SIM800.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",\"80\"");  //start up the connection
    delay(6000);

    ShowSerialData();

    SIM800.println("AT+CIPSEND");  //begin send data to remote server
    delay(4000);
    ShowSerialData();

    String str = "GET https://api.thingspeak.com/update?api_key=FSHQHRIUH2UDFWDB&field1=" + String(mV_value) + "&field2=" + String(mA_value) + "&field3=" + String(t.getTemperature(0)) + "&field4=" + String(dh.getT(0)) + "&field5=" + String(dh.getH(0)) + "&field6=" + String(interferance_value) + "&field7=" + String(l.getLat(0)) + "&field8=" + String(l.getLon(0));
    Serial.println(str);
    SIM800.println(str);  //begin send data to remote server

    delay(4000);
    ShowSerialData();

    SIM800.println((char)26);  //sending
    delay(5000);               //waitting for reply, important! the time is base on the condition of internet
    SIM800.println();

    ShowSerialData();

    SIM800.println("AT+CIPSHUT");  //close the connection
    delay(100);
    ShowSerialData();
  }
}
void ShowSerialData() {
  while (SIM800.available() != 0)
    Serial.write(SIM800.read());
  delay(5000);
}