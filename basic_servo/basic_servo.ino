#include <Servo.h>

Servo servo1;
//object of servo class
int pwm = 4;
//pin 4 on board

void setup() {
  // put your setup code here, to run once:

servo1.attach(pwm);


}

void loop() {
  
  // put your main code here, to run repeatedly:
  servo1.write(90);
  
  delay(1000);
  servo1.write(0);

  delay(1000);
  servo1.write(180);
  
  delay(1000);

}
