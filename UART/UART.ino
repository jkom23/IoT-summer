#include <SoftwareSerial.h>
SoftwareSerial mySerialPort(4, 5); //RX, TX

char msgIn, msgOut;
bool isJack = false;
void setup() {
  Serial.begin(9600);
  mySerialPort.begin(9600);
}

void loop() {
  //while i have data in software serial buffer
  while(mySerialPort.available()) {
    if(isJack){
      Serial.print("You: ");
      isJack=false;
    }
    msgIn = mySerialPort.read();
    Serial.print(msgIn);
    delay(2);
    
  }
  //while I have data in serial buffer
  while(Serial.available()){
    if(!isJack){
      Serial.print("Jack: ");
      isJack=true;
    }
    msgOut = Serial.read(); //read each char in order to send it
    mySerialPort.write(msgOut);// send char
    Serial.print(msgOut);
    delay(2);
  }
}
