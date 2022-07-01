void mellopad_Th(float Min, float Max) {
  digitalWrite(control, HIGH);
  Mellopad_T.requestTemperatures();
  tempC = Mellopad_T.getTempCByIndex(0);  //(Mellopad_T.getTempFByIndex(0));

  Serial.print("Celsius temperature: "); //(" - Fahrenheit temperature: ");
  Serial.println(tempC);

  // delay(100);

  int range = ((((Min + Max) / 2)) + 2);
   
  if ((((tempC)  <= ((((Min + Max) / 2)) + 2)))) {
    digitalWrite(heater_Pin1, HIGH);
    Neomellopad1();
    flag1 = true;
  } else {
    flag1 = false;
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
    if ((counterT % 2 == 0)) {
      digitalWrite(heater_Pin1, (((tempC)  <= (Min)) && (((tempC)  = ! (Max) + 2))) ? HIGH : LOW);
      Serial.println(heater_Pin1);
      Serial.println("ONcounter");
      Neomellopad3();
    }
    else {
      digitalWrite(heater_Pin1, LOW);
      Neomellopad2();
    }
    // digitalWrite(heater_Pin1control, (((tempC)  <= (Min)) && ((tempC) < (Min + 9))) ? HIGH : LOW);
  }
}