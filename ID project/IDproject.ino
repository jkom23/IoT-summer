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
#include <Adafruit_STMPE610.h>
#include <Adafruit_ILI9341.h>
#include "image.h"
#include "large.h"

#define STMPE_CS 16
#define TFT_CS   0
#define TFT_DC   15
#define SD_CS    2

#define TS_MAXX 100
#define TS_MINX 3800
#define TS_MINY 100
#define TS_MAXY 3750
TS_Point p;

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);
#define BoxSize 40


bool detectTouch() {
  p = ts.getPoint();

  if (p.x < TS_MINX && p.x > TS_MAXX && p.y < TS_MAXY && p.y > TS_MINY) {
    //map values to pixel scale
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());

    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);
    //detech touch in box
    if (p.x > BoxSize * 0 && p.x < BoxSize * 6 && p.y > BoxSize * 3 &&  p.y < BoxSize * 8) {
      return true;
    }
  } return false;
}

void drawID(){
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
  tft.setCursor(40, 45);
  tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(2);
  tft.println("Jack Komaroff");
  tft.setCursor(40, 65);
  tft.println("Class of: 2023");
 tft.setCursor(30, 85);
  tft.setTextColor(ILI9341_BLACK);  tft.setTextSize(2);
  tft.println("*4HMLL00398421*");
  tft.drawRGBBitmap(5, 100, self, 230, 230);
}

void setup() {
  Serial.begin(115200);
  delay(10);
  ts.begin();
  tft.begin();
  delay(20);
  drawID();

}

void loop() {
  
  yield();
  if (detectTouch()) {
    delay(200);
    if (detectTouch()) {
      tft.fillScreen(ILI9341_WHITE);
      tft.drawRGBBitmap(0, 0, finalscreenlarge, 230, 310);
      delay(6000);
      drawID();
    }
  
  }
  delay(50);
}
