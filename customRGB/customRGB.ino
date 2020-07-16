int RED= 2;
int GREEN =5;
int BLUE = 4;
void setup() {
    // Initialize the LED_BUILTIN pin as an output
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);

  analogWriteRange(255);
  digitalWrite(RED, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite(GREEN, HIGH);
  
}

// the loop function runs over and over again forever
void loop() {
  analogWrite(RED, 127);
  
  for(int i = 0; i<=255; i++){
    analogWrite(BLUE,0+i);
    analogWrite(GREEN,0-i);

    delay(10);
    
  }
   analogWrite(RED, 0);
   analogWrite(BLUE,0);
}
