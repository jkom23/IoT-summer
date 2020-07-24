//preprocessor includes

#include <MiniGrafx.h>
#include "ILI9341_SPI.h"
#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include "NTPClientUpdated.h"
#include "sunicon.h"
#include "fonts.h"
#include "weatherlogo.h"
#include <OpenWeatherMapCurrent.h>
#include <OpenWeatherMapForecast.h>

//preprocessor defines

#define WIFI_SSID "6E"
#define WIFI_PASS "SPECTRAAUDIO"
#define MAX_FORECAST 3

//pinout for lcd screen and touchscreen
#define STMPE_CS 16
#define TFT_CS 0
#define TFT_DC 15
#define SD_CS 2
#define TFT_LED 5

//custom color palette
#define BLACK_COLOR 0x0000
#define WHITE_COLOR 0xFFFF
#define BLUE_COLOR 0x059F
#define ORANGE_COLOR 0xFCA0



//Define time constraints

WiFiUDP ntpUDP;
const long utcOffsetInSeconds = -4 * 3600;  // -4 UTC Offset / NYC
NTPClientUpdated timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

//initializations

String timeStamp;
String dateStamp;
int screen =1;
bool isDebug = false;

//weather settings

String OPEN_WEATHER_MAP_LANGUAGE = "en"; //english - my native language
String OPEN_WEATHER_MAP_APPID = "6eb55a02ea9abdc2de5fa8f132681dc4"; //default key
String OPEN_WEATHER_MAP_LOCATION = "New York,NY,US"; //where I primarily live
const boolean IS_METRIC = false; //keep false for farenheit - true for celcius

// Weather objects

OpenWeatherMapCurrentData currentWeather;
OpenWeatherMapForecastData forecasts[MAX_FORECAST];

//graphics library initalizations
int BITS_PER_PIXEL = 2; //2 ^ 2 colors

uint16_t palette[] = {
  BLACK_COLOR, //0
  WHITE_COLOR, //1
  BLUE_COLOR, //2
  ORANGE_COLOR, //3

};

ILI9341_SPI tft = ILI9341_SPI(TFT_CS, TFT_DC);
MiniGrafx gfx = MiniGrafx(&tft, BITS_PER_PIXEL, palette);



void powerOn() {

  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);
  gfx.init();
}

void WiFiSetup() {

  if (WiFi.status() == WL_CONNECTED) return;
  Serial.print(WIFI_SSID);
  Serial.print("/");
  Serial.println(WIFI_PASS);
  Serial.print("Connecting to the WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  int i = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    if (i>90){
      i=0;
    }
    i+=10;
    drawProgress(i, "Connecting to WiFi (" + String(WIFI_SSID) + ")");
    Serial.print(".");
  }
  drawProgress(100, "Connected to WIFI (" + String(WIFI_SSID) + ")");
  Serial.println("\nConnected to the WiFi");
}

void updateTimeWeather() {

  while (!timeClient.forceUpdate()) {
    timeClient.forceUpdate();
  }

  if (millis() % 3600000 < 1500) {
    updateWeatherData();

  }

  if (millis() % 8000 < 150) {
    if(screen ==1){
      screen =2;
    }else if(screen ==2){
      screen =1;
    }

  }

  timeStamp = timeClient.getFormattedTime();
  dateStamp = timeClient.getFormattedDate();

  
}

void printTimeWeather() {
  
  updateTimeWeather();
  
  if (screen == 1){
    weatherScreen();
  }else if (screen == 2){
    todaysInformation();
  }
  
//  if (isDebug){
//  Serial.println("Time: " + timeStamp);
//  Serial.println("Date: " + dateStamp);
//  Serial.println("Pressure: " + String(currentWeather.pressure) + " mb");
//  Serial.println("Latitude: " + String(currentWeather.lat));
//  Serial.println("Longitude: " + String(currentWeather.lon));
//  Serial.println("Temperature: " + String(int(round(currentWeather.temp))) + "°F" );
//  Serial.println("3 Hour Forecast: " + String((int(round(forecasts[0].temp)))) + "°F");
////  Serial.println("6 Hour Forecast: " + String((int(round(forecasts[1].temp)))) + "°F");
//  Serial.println("9 Hour Forecast: " + String((int(round(forecasts[2].temp)))) + "°F");
//  Serial.println("--------------------------------------------------------------");
//  delay(1000);
//}
}
void timeSetup() {

  timeClient.begin();
}

void weatherScreen(){
  gfx.fillBuffer(0);
  
  
  gfx.setFont(Syncopate_Bold_16);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setColor(1);
  gfx.drawString(120, 20, timeStamp);
  
  
  gfx.setFont(Syncopate_Bold_16);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setColor(1);
  gfx.drawString(120, 55, dateStamp);

  //TEMP
  gfx.setFont(Schoolbell_Regular_25);
  gfx.setTextAlignment(TEXT_ALIGN_RIGHT);
  gfx.setColor(1);
  gfx.drawString (215, 110, ("Temp: " + String(int(round(currentWeather.temp))) + "°F" ));
  gfx.drawPalettedBitmapFromPgm(0,80,getMeteoconIconFromProgmem(currentWeather.icon));
  //discription
  gfx.setFont(Roboto_Mono_14);
  gfx.setColor(1);
  gfx.drawString (220, 140, (String(currentWeather.description)));

  //forecast 3hour
  gfx.setFont(Roboto_Mono_14);
  
  gfx.setColor(1);
  gfx.drawString (55, 230, (String((int(round(forecasts[0].temp)))) + "°F" ));
  gfx.drawString (55, 245, ("3 Hour"));
  gfx.drawPalettedBitmapFromPgm(20,180,getMiniMeteoconIconFromProgmem(forecasts[0].icon));
  //forecast 6hour
  gfx.setFont(Roboto_Mono_14);

  gfx.setColor(1);
  
  
  gfx.drawString (135, 245, ("6 Hour"));
  gfx.drawString (135, 230, (String((int(round(forecasts[1].temp)))) + "°F" ));
  gfx.drawPalettedBitmapFromPgm(95,180,getMiniMeteoconIconFromProgmem(forecasts[1].icon));
  
//forecast 9hour
  gfx.setFont(Roboto_Mono_14);

  gfx.setColor(1);
  
  
  gfx.drawString (215, 230, (String((int(round(forecasts[2].temp)))) + "°F" ));
  gfx.drawString (215, 245, ("9 Hour"));
  gfx.drawPalettedBitmapFromPgm(175,180,getMiniMeteoconIconFromProgmem(forecasts[2].icon));
//location
  gfx.setFont(Schoolbell_Regular_25);

  gfx.setColor(3);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.drawString (120, 280, (String(currentWeather.cityName)));

 
 

  
  gfx.commit();

  
}

void updateForecast(){
  OpenWeatherMapForecast *forecastClient = new OpenWeatherMapForecast();
  forecastClient->setMetric(IS_METRIC);
  forecastClient->setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
  forecastClient->updateForecasts(forecasts, OPEN_WEATHER_MAP_APPID, OPEN_WEATHER_MAP_LOCATION, MAX_FORECAST);
  delete forecastClient;
  forecastClient = nullptr;
}

void updateCurrent(){
  OpenWeatherMapCurrent *currentWeatherClient = new OpenWeatherMapCurrent();
  currentWeatherClient->setMetric(IS_METRIC);
  currentWeatherClient->setLanguage(OPEN_WEATHER_MAP_LANGUAGE);
  currentWeatherClient->updateCurrent(&currentWeather, OPEN_WEATHER_MAP_APPID, OPEN_WEATHER_MAP_LOCATION);
  delete currentWeatherClient;
  currentWeatherClient = nullptr;
}
void updateWeatherData() {
  drawProgress(50, "Updating Current Weather...");
  updateCurrent();
  updateForecast();
  delay(100);
}

void serialSetup() {

  Serial.begin(115200);
  //if random characters are showing--> uncomment the following line
  Serial.print("\n\n\n");
}

void welcomeScreen() {
  gfx.fillBuffer(0);
  gfx.setColor(1);
  gfx.setFont(Syncopate_Bold_16);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.drawString(120, 30, "WEATHER STATION");
  gfx.drawPalettedBitmapFromPgm(60, 100, sunicon);
  gfx.setFont(Roboto_Mono_14);
  gfx.setColor(1);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.drawString(120, 300, "© 2020, Jack Komaroff");
  gfx.commit();
}

void drawProgress(int percentage, String text) {
  gfx.fillBuffer(0);
  gfx.setColor(1);
  gfx.setFont(Syncopate_Bold_16);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.drawString(120, 30, "WEATHER STATION");
  gfx.drawPalettedBitmapFromPgm(60, 100, sunicon);
//bar
  gfx.setColor(2);//blue
  gfx.drawRect(10, 225, 220, 15);
  gfx.setColor(2);
  gfx.fillRect(12, 227, 216 * percentage/100, 11); 
  //text for info
  gfx.setColor(1);
  gfx.setFont(Roboto_Mono_14);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.drawString(120,245,text);
  
  gfx.setFont(Roboto_Mono_14);
  gfx.setColor(1);
  gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.drawString(120, 300, "© 2020, Jack Komaroff");
  gfx.commit();
}

void todaysInformation(){
  gfx.fillBuffer(0);
gfx.setTextAlignment(TEXT_ALIGN_LEFT);
gfx.setFont(Roboto_Mono_14);
  gfx.setColor(1);
  gfx.drawString(10, 10, "Temperature (Min): " + String(int(round(currentWeather.tempMin))) + "°F" );
  gfx.drawString(10, 40, "Temperature (Max): " + String(int(round(currentWeather.tempMax))) + "°F" );
  gfx.drawString(10, 70, "Pressure: " + String(currentWeather.pressure) + " mb" );
  gfx.drawString(10, 130, "Sunrise: " + String(timeClient.getFormattedTime(true,currentWeather.sunrise + utcOffsetInSeconds)));
  gfx.drawString(10, 100, "Humidity: " + String(currentWeather.humidity) + "%" );
  gfx.drawString(10, 160, "Sunset: " + String(timeClient.getFormattedTime(true,currentWeather.sunset + utcOffsetInSeconds)));
  gfx.commit();
}

void setup() {
  // put your setup code here, to run once:
  powerOn();
  serialSetup();
  welcomeScreen();
  delay(1000);
  WiFiSetup();
  updateWeatherData();
  timeSetup();
}

void loop() {
  // put your main code here, to run repeatedly:

  printTimeWeather();
}
