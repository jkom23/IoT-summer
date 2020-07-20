/***************************************************
  This is our GFX example for the Adafruit ILI9341 TFT FeatherWing
  ----> http://www.adafruit.com/products/3315

  Check out the links above for our tutorials and wiring diagrams

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "image.h"

#ifdef ESP8266
#define STMPE_CS 16
#define TFT_CS   0
#define TFT_DC   15
#define SD_CS    2
#endif
#ifdef ESP32
#define STMPE_CS 32
#define TFT_CS   15
#define TFT_DC   33
#define SD_CS    14
#endif
#ifdef TEENSYDUINO
#define TFT_DC   10
#define TFT_CS   4
#define STMPE_CS 3
#define SD_CS    8
#endif
#ifdef ARDUINO_STM32_FEATHER
#define TFT_DC   PB4
#define TFT_CS   PA15
#define STMPE_CS PC7
#define SD_CS    PC5
#endif
#ifdef ARDUINO_NRF52832_FEATHER /* BSP 0.6.5 and higher! */
#define TFT_DC   11
#define TFT_CS   31
#define STMPE_CS 30
#define SD_CS    27
#endif
#if defined(ARDUINO_MAX32620FTHR) || defined(ARDUINO_MAX32630FTHR)
#define TFT_DC   P5_4
#define TFT_CS   P5_3
#define STMPE_CS P3_3
#define SD_CS    P3_2
#endif

// Anything else!
#if defined (__AVR_ATmega32U4__) || defined(ARDUINO_SAMD_FEATHER_M0) || defined (__AVR_ATmega328P__) || \
    defined(ARDUINO_SAMD_ZERO) || defined(__SAMD51__) || defined(__SAM3X8E__) || defined(ARDUINO_NRF52840_FEATHER)
#define STMPE_CS 6
#define TFT_CS   9
#define TFT_DC   10
#define SD_CS    5
#endif


Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);

void setup() {
  Serial.begin(115200);

  delay(10);
  Serial.println("FeatherWing TFT Test!");

  tft.begin();

  // read diagnostics (optional but can help debug problems)
  uint8_t x = tft.readcommand8(ILI9341_RDMODE);
  Serial.print("Display Power Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDMADCTL);
  Serial.print("MADCTL Mode: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDPIXFMT);
  Serial.print("Pixel Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDIMGFMT);
  Serial.print("Image Format: 0x"); Serial.println(x, HEX);
  x = tft.readcommand8(ILI9341_RDSELFDIAG);
  Serial.print("Self Diagnostic: 0x"); Serial.println(x, HEX);

  Serial.println(F("Benchmark                Time (microseconds)"));
  delay(10);
  Serial.print(F("Jack's ID Card              "));

  delay(500);

  jackID();



}


void loop(){
  
}
void jackID() {
  
  tft.fillScreen(ILI9341_BLACK);
  yield();
  tft.fillScreen(ILI9341_WHITE);
  yield();
  tft.setCursor(12, 15);
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(2);
  tft.println("HORACE MANN SCHOOL");
  tft.setCursor(3, 35);
  tft.setTextColor(ILI9341_RED);  tft.setTextSize(1);
  tft.println("231 West 246th Street; Bronx, NY, 10471");
  tft.setCursor(40,45);
   tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(2);
  tft.println("Jack Komaroff");
  tft.setCursor(40,65);
  tft.println("Class of: 2023");
  tft.setCursor(30,85);
  tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(2);
  tft.println("*4HMLL00398421*");
  tft.drawRGBBitmap(0,100,self, image_width, image_height);
  yield();
 
}



 
