#define IN1 5 // 
#define IN2 6 //
#define IN3 2 //
#define IN4 3//

#define JOYSTICK_Y_PIN A2
#define JOYSTICK_X_PIN A1

int xBase;
int yBase;
int bValue = 0 ;

void setup() {
  Serial.begin(115200);
  delay(100); pinMode(8, INPUT);
  digitalWrite(8, HIGH);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  xBase = analogRead(JOYSTICK_X_PIN);
  yBase = analogRead(JOYSTICK_Y_PIN);
}

void loop() {
  joystickDrive();

  bValue = digitalRead(8);
}

void joystickDrive() {
  int pawa = abs(analogRead(JOYSTICK_Y_PIN) - yBase) / 2;
  boolean dir = (analogRead(JOYSTICK_Y_PIN) > yBase);
  int steeringPawa = abs(analogRead(JOYSTICK_X_PIN) - xBase) / 2;
  boolean steeringDir = (analogRead(JOYSTICK_X_PIN) > xBase);
  if (pawa > 20) {
    if (steeringPawa < 20) {
      if (dir) { // forward
        forward(pawa, pawa);
      }
      else { // backward
        backward(pawa, pawa);
      }
    }
    else {
      if (dir) {
        if (steeringDir) { // forward right
          forward(constrain(pawa - steeringPawa, 0, pawa), pawa);
        }
        else { // forward left
          forward(pawa, constrain(pawa - steeringPawa, 0, pawa));
        }
      }
      else {
        if (steeringDir) { // backward right
          backward(pawa - steeringPawa, pawa);
        }
        else {
          Serial.println("backward left");
          backward(pawa, pawa - steeringPawa);//
        }
      }
    }
  }
  else if (steeringPawa > 20) {
    if (steeringDir) { // right
      right(steeringPawa);
    }
    else { // left
      left(steeringPawa);
    }
  }
  else stopp();
}

void forward(int speed1, int speed2) {
  Serial.println("backward");//forward
  drive(false, false, (speed1 - 25), speed2);
 ;
}

void backward(int speed1, int speed2) {
  Serial.println("forward");//forward
  drive(true, true, speed1, speed2);

  
}

void right(int speed) {
 
  Serial.println("left");
  drive(false, false, speed, (speed - speed));// change
}

void left(int speed) {
  
  Serial.println("right"); //Serial.println("right");
  drive(false
  false, speed, speed); //
}

void drive(boolean dir1, boolean dir2, int speed1, int speed2) {
  speed1 = constrain(speed1, 0, 1023);
  speed2 = constrain(speed2, 0, 1023);
  Serial.print(dir1 ? "" : "-");
  Serial.print(speed1);
  Serial.print(dir2 ? "\t" : "\t-");
  Serial.print(speed2);
  Serial.println();
  if (dir1) {
    digitalWrite(IN1, LOW);
    analogWrite(IN2, speed1);
    // Serial.println("dir 1");
  }
  else {
    digitalWrite(IN1, HIGH);
    analogWrite(IN2, 255 - speed1);
    // Serial.println("Pinopp 1");
  }
  yield();
  if (dir2) {
    analogWrite(IN3, 255 - speed2);
    digitalWrite(IN4, HIGH);
    // Serial.println("dir 2");
  }
  else {
    analogWrite(IN3, speed2);
    digitalWrite(IN4, LOW);
    // Serial.println("oppdir 2");
  }
}

void stopp() {
  //  Serial.println("stop");
  drive(true, true, 0, 0);
}
