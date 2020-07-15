int ldr_pin = A0;
int analogValue = 0;
int LED_PIN = 5;
int LED_PIN2 = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogValue = analogRead(ldr_pin);
Serial.print("LDR Value is: ");
Serial.println(analogValue);
delay(50);
if(analogValue>401&&analogValue<700){
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_PIN2, HIGH);
}else if(analogValue>700){
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(LED_PIN2, HIGH);
}else if(analogValue<400){
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_PIN2, LOW);
}


}
