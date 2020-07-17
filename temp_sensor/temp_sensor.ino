#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  Serial.println("DHT Test");
  dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:

  float t= dht.readTemperature(true);
  float h = dht.readHumidity();
  float c = dht.convertFtoC(t);
  
  Serial.printf("\nThe Temperature in the room is %f", t);
  Serial.printf("\nThe Humidity in the room is %f", h);
  Serial.printf("\nThe Temp in Celcius in the room is %f", c);
  
  delay(2000);
}
