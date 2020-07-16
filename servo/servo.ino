#include <Servo.h>
int analogValue = 0;
Servo servo1;
//object of servo class
int pwm = 4;
//pin 4 on board

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo1.attach(pwm);


}

void loop() {
  // put your main code here, to run repeatedly:
  int LDR = analogRead(A0);
  Serial.print("LDR Value is: ");
  Serial.println(LDR);
  delay(50);
  int pwmOut;
  pwmOut = map(LDR, 0, 1024, 0, 180);
  Serial.println(pwmOut);
  servo1.write(pwmOut);


}
