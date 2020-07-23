#include <Adafruit_GFX.h>
#include <Adafruit_STMPE610.h>
#include <Adafruit_ILI9341.h>
#include <DHT.h>


//ESP8266
#define STMPE_CS 16 // chip select
#define TFT_CS   0 //tft
#define TFT_DC   15 // multiplex- data + clock
#define SD_CS    2

#define LED_PIN 14
#define TS_MAXX 100
#define TS_MINX 3800
#define TS_MINY 100
#define TS_MAXY 3750


#define box 40

TS_Point p;
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_STMPE610 ts = Adafruit_STMPE610(STMPE_CS);

bool detectTouch(int xpos, int ypos, int width, int height) {
  p = ts.getPoint();
delay(50);
  if (p.x < TS_MINX && p.x > TS_MAXX && p.y > TS_MINY && p.y < TS_MAXY) {
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());

    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);

    if ( p.x > xpos && p.x < width + xpos  && p.y > ypos && p.y < ypos + height) {

      Serial.println("Detected");
      return true;

    }
  }
  return false;
}

void drawButton(char *string, int xpos, int ypos) {
  tft.drawRect(xpos, ypos, box * 4, box * 1.5, ILI9341_WHITE);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
  tft.setCursor(xpos + box * 1, ypos + box * 0.5);
  tft.print(string);
  yield();
}

void drawWelcome() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_MAGENTA);
  tft.setTextSize(3);
  tft.setCursor(box * 1.5, box * 1);
  tft.println("WELCOME");
  drawButton("DHT", box * 1, box * 2);
  drawButton("LED", box * 1, box * 4);
  while (1) {
    if (detectTouch(box * 1, box * 4, box * 4, box * 1.5)) {
      delay(100);
      if (detectTouch(box * 1, box * 4, box * 4, box * 1.5)) {
        drawLED();
        break;
      }
    }
    delay(10);
  }
}

void drawLED() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_RED);
  tft.setTextSize(3);
  tft.setCursor(box * 0.85, box * 2);
  tft.println("LED Control");
  drawButton("I/O", box * 1, box * 4);
  drawButton("BACK", box * 1, box * 6);

  //toggle led
  while (1) {

    if (detectTouch(box * 1, box * 4, box * 4, box * 1.5)) {
      Serial.println("IO");
      delay(150);
      if (detectTouch(box * 1, box * 4, box * 4, box * 1.5)) {
        Serial.print("LED detected");
        digitalWrite(LED_PIN, !(digitalRead(LED_PIN)));
        continue;
      }
    }
    //back
    if (detectTouch(box * 1, box * 6, box * 4, box * 1.5)) {
      Serial.println("Back button");
      delay(150);
      if (detectTouch(box * 1, box * 6, box * 4, box * 1.5)) {
        Serial.println("inside the back button");
        drawWelcome();
        break;
      }
    }
    delay(20);
  }
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  ts.begin();
  tft.begin();
  drawWelcome();
}

void loop() {
  // put your main code here, to run repeatedly:


}
