#include <Servo.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22
int REDled = 0;
int GREENled = 16;
int BLUEled = 2;
DHT dht(DHTPIN, DHTTYPE);
int analogValue = 0;
Servo servo1;
//object of servo class
int pwm = 5;
//pin 4 on board

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo1.attach(pwm);
  Serial.println("DHT Test");
  dht.begin();
  pinMode(REDled, OUTPUT);
  pinMode(GREENled, OUTPUT);
  pinMode(BLUEled, OUTPUT);

  analogWriteRange(255);
  digitalWrite(REDled, HIGH);
  digitalWrite(BLUEled, HIGH);
  digitalWrite(GREENled, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:

  float t = dht.readTemperature(true);

  if (isnan(t)) {
    Serial.print(F("Error getting the value"));
    return;
  }
  Serial.printf("\nThe Temperature in the room is %f", t);


  delay(2000);

  int pwmOut;
  pwmOut = map(t, 0, 90, 0, 180);
  //Serial.println(t);
  servo1.write(pwmOut);
  if (t <= 32) {
    digitalWrite(BLUEled, LOW);
    digitalWrite(REDled, HIGH);
    digitalWrite(GREENled, HIGH);
  } else if (t > 32 && t <= 68) {
    digitalWrite(GREENled, LOW);
    digitalWrite(REDled, LOW);
    digitalWrite(BLUEled, HIGH);
  } else {
    digitalWrite(REDled, LOW);
    digitalWrite(BLUEled, HIGH);
    digitalWrite(GREENled, HIGH);
  }

}
