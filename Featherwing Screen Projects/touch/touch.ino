
#include <Adafruit_GFX.h>
#include <Adafruit_STMPE610.h>
#include <Adafruit_ILI9341.h>


//config
//draw on GUI
//code for getting touch points


//ESP8266
#define STMPE_CS 16 // chip select
#define TFT_CS   0 //tft
#define TFT_DC   15 // multiplex- data + clock
#define SD_CS    2

#define TS_MAXX 100
#define TS_MINX 3800
#define TS_MINY 100
#define TS_MAXY 3750

TS_Point p;
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

#define BoxSize 40

void drawButton() {

  tft.fillScreen(ILI9341_BLACK);
  //clear screen

  //make box
  tft.fillRect(BoxSize * 1, BoxSize * 1, BoxSize * 4, BoxSize * 2, ILI9341_MAGENTA);
  //text
  tft.setCursor(BoxSize * 1.5, BoxSize * 1.8);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLUE);
  tft.println("TOUCH HERE");
}

void drawPress(int x, int y) {
  tft.setCursor(BoxSize * 1.9, BoxSize * 5.5);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_GREEN);
  Serial.println("DETECTED");
  tft.println("PRESSED");
  tft.setCursor(BoxSize * 0.88, BoxSize * 6.5);
  tft.printf("X: %d | Y: %d", x, y);
}

bool detectTouch(int xpos, int ypos, int width, int height) {
  p = ts.getPoint();


  if (p.x < TS_MINX && p.x > TS_MAXX && p.y < TS_MAXY && p.y > TS_MINY) {
    //map values to pixel scale
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());

    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());


    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);
    //detech touch in box
    if (p.x > BoxSize * 1 && p.x < BoxSize * 5 && p.y > BoxSize * 1 &&  p.y < BoxSize * 3) {
      return true;
    }

  } return false;
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //init
  if (!ts.begin()) {
    Serial.print("ERROR: STMPE error");
  }
  tft.begin();

  drawButton();
}


void loop() {
  // put your main code here, to run repeatedly:


  if (detectTouch()) {
    delay(200);
    if (detectTouch()) {
      drawPress(p.x, p.y);
      delay(500);
      drawButton();
      yield();
    }
  }


  if (detectTouch()) {

    drawPress(p.x, p.y);
    delay(500);
    drawButton();
    yield();
  }
}
