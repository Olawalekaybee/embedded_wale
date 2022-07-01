

#define SENSOR_PIN  0
#define RPWM_Output  5 // Arduino PWM output pin 5; connect to IBT-2 pin 1 (RPWM)
#define LPWM_Output 6

#define RPWM2_Output 2   // (secRPWM)
#define LPWM2_Output 3  // (secLPWM)

void setup()
{
  pinMode(RPWM_Output, OUTPUT);
  pinMode(RPWM2_Output, OUTPUT);
  pinMode(LPWM_Output, OUTPUT);
  pinMode(LPWM2_Output, OUTPUT);
  Serial.begin(115200);
}
void loop()
{
  int sensorValue = analogRead(SENSOR_PIN);
  Serial.print("GET_sensorValue: \t");
  Serial.println(sensorValue);

  if (sensorValue < 512)
  {
    // reverse rotation
    int reversePWM = -(sensorValue - 511) / 2;
    analogWrite(LPWM_Output, 0);
    analogWrite(RPWM_Output, reversePWM);
    analogWrite(LPWM2_Output, 0);
    analogWrite(RPWM2_Output, reversePWM);
  }

  else
  {
    // forward rotation
    int forwardPWM = (sensorValue - 512) / 2;
    analogWrite(LPWM_Output, forwardPWM);
    analogWrite(RPWM_Output, 0);
    analogWrite(LPWM2_Output, forwardPWM);
    analogWrite(RPWM2_Output, 0);
  }
}