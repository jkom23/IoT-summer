//preprocessor includes

#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include "NTPClientUpdated.h"
#include <OpenWeatherMapCurrent.h>
#include <OpenWeatherMapForecast.h>

//preprocessor defines

#define WIFI_SSID "6E"
#define WIFI_PASS "SPECTRAAUDIO"
#define MAX_FORECAST 3



//Define time constraints
WiFiUDP ntpUDP;
const long utcOffsetInSeconds = -4 * 3600;  // -4 UTC Offset / NYC
NTPClientUpdated timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

//initializations
String timeStamp;
String dateStamp;

//weather settings

String OPEN_WEATHER_MAP_LANGUAGE = "en"; //english - my native language
String OPEN_WEATHER_MAP_APPID = "6eb55a02ea9abdc2de5fa8f132681dc4"; //default key
String OPEN_WEATHER_MAP_LOCATION = "New York,NY,US"; //where I primarily live
const boolean IS_METRIC = false; //keep false for farenheit - true for celcius

// Weather objects
OpenWeatherMapCurrentData currentWeather;
OpenWeatherMapForecastData forecasts[MAX_FORECAST];


void WiFiSetup() {

  if (WiFi.status() == WL_CONNECTED) return;
  Serial.print(WIFI_SSID);
  Serial.print("/");
  Serial.println(WIFI_PASS);
  Serial.print("Connecting to the WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to the WiFi");
}

void updateTimeWeather() {
  while (!timeClient.forceUpdate()) {
    timeClient.forceUpdate();
  }

  updateWeatherData();

  timeStamp = timeClient.getFormattedTime();
  dateStamp = timeClient.getFormattedDate();
}

void printTimeWeather() {

  updateTimeWeather();

  Serial.print("Time: ");
  Serial.println(timeStamp);
  Serial.print("Date: ");
  Serial.println(dateStamp);
  Serial.print("Temp: ");
  Serial.println(currentWeather.temp);
  Serial.println("3 Hour Forecast:");
  Serial.print("Temp: ");
  Serial.println(forecasts[0].temp);
  Serial.println("6 Hour Forecast:");
  Serial.print("Temp: ");
  Serial.println(forecasts[1].temp);
  Serial.println("9 Hour Forecast:");
  Serial.print("Temp: ");
  Serial.println(forecasts[2].temp);
  Serial.println("--------------------------------------------------------------");
  delay(1000);
}

void timeSetup() {

  timeClient.begin();
}

void updateWeatherData() {

  //current weather
  OpenWeatherMapCurrent *currentWeatherClient = new OpenWeatherMapCurrent();
  currentWeatherClient->setMetric(IS_METRIC);
  currentWeatherClient->setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
  currentWeatherClient->updateCurrent(&currentWeather, OPEN_WEATHER_MAP_APPID, OPEN_WEATHER_MAP_LOCATION);
  delete currentWeatherClient;
  currentWeatherClient = nullptr;

  //forecast weather
  OpenWeatherMapForecast *forecastClient = new OpenWeatherMapForecast();
  forecastClient->setMetric(IS_METRIC);
  forecastClient->setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
  forecastClient->updateForecasts(forecasts, OPEN_WEATHER_MAP_APPID, OPEN_WEATHER_MAP_LOCATION, MAX_FORECAST);
  delete forecastClient;
  forecastClient = nullptr;

  //delay for proccessing
  delay(100);
}

void setup() {
  // put your setup code here, to run once:
  //if random characters are showing--> uncomment the following line
  Serial.begin(115200);
  Serial.print("\n\n\n");
  WiFiSetup();
  timeSetup();
}

void loop() {
  // put your main code here, to run repeatedly:
  printTimeWeather();

}
