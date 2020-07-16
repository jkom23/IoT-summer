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
  digitalWrite(RED, LOW);  
  
  //digitalWrite(GREEN, LOW);//for yellow
  delay(500);                      // Wait for a second
  digitalWrite(RED, HIGH);  // Turn the LED off by making the voltage HIGH
  //digitalWrite(GREEN, HIGH);//for yellow
    digitalWrite(BLUE, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  //digitalWrite(RED, LOW);
  delay(500);                      // Wait for a second
 // digitalWrite(RED, HIGH);  // purple
   digitalWrite(BLUE, HIGH);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  digitalWrite(GREEN, LOW);
  // digitalWrite(BLUE, LOW);
  delay(500);                      // Wait for a second
//  digitalWrite(BLUE, HIGH);  // cyan    
  digitalWrite(GREEN, HIGH);              
}
