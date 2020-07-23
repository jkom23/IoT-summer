
#include <Adafruit_GFX.h>
#include <Adafruit_STMPE610.h>
#include <Adafruit_ILI9341.h>
#include <SPI.h>
#define box 40
#include "paper.h"
#include "rock.h"
#include "scissors.h"
#include "cont.h"
#include "dragon.h"
#include "fire.h"


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
//      Function to draw boxes for pictures
void drawBox (char *string, int xpos, int ypos) {
  //             x    y  width height    color
  tft.drawRect(xpos, ypos, box * 4, box * 1.5, ILI9341_GREEN);
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(3);
  tft.setCursor(xpos + box * 0.2, ypos + box * 0.5);
  tft.print(string);
}

void drawButton(){
  tft.fillScreen(ILI9341_BLACK);
  tft.fillRect(0, 0, box * 6, box, ILI9341_RED);
  tft.setCursor(box+23, 0);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_BLACK);
  tft.println("GET READY");
  tft.setCursor(box-10, box/2);
  tft.println("FOR THE HARDEST");
  tft.fillRect(0, box, box * 6, box, ILI9341_BLACK);
  tft.setCursor(0+17, box+10);
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("GAME OF YOUR LIFE");
  tft.drawRGBBitmap(72, box*3, dragon, DRAGON_WIDTH, DRAGON_HEIGHT);
  tft.drawRGBBitmap(6, box*3, fire, FIRE_WIDTH, FIRE_HEIGHT);
  tft.drawRGBBitmap(170, box*3, fire, FIRE_WIDTH, FIRE_HEIGHT);
  tft.drawRGBBitmap(2, box*5, cont, cont_WIDTH, cont_HEIGHT);
}
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
int aiChoice;
int playerChoice;

void AI() {
  aiChoice = random(1, 3);
  if (detectTouch(box * 1, box * 1.8, box * 4, box * 1.5)) {
    delay(200);
    if (detectTouch(box * 1, box * 1.8, box * 4, box * 1.5)) {
      playerChoice = 1;
      if (aiChoice == 2) {
        tft.setTextColor(ILI9341_GREEN);
        tft.setTextSize(1);
        tft.setCursor(box * 0, box * 7);
        tft.print("AI had paper. You lose!");
        delay(5000);
        tft.fillScreen(ILI9341_BLACK);
        drawButton();
        delay(2000);
        drawScreen();
        
      } else if (aiChoice = 1) {
        tft.setTextColor(ILI9341_GREEN);
        tft.setTextSize(1);
        tft.setCursor(box * 0, box * 7);
        tft.print("AI had rock. Tie!");
        delay(5000);
        tft.fillScreen(ILI9341_BLACK);
        drawButton();
        delay(2000);
        drawScreen();
        
      } else {
        tft.setTextColor(ILI9341_GREEN);
        tft.setTextSize(1);
        tft.setCursor(box * 0, box * 7);
        tft.print("AI had scissors. You win!");
        delay(5000);
        tft.fillScreen(ILI9341_BLACK);
        drawButton();
        delay(2000);
        drawScreen();
      }
    }
  }
  delay(10);
  if (detectTouch(box * 1, box * 3.5, box * 4, box * 1.5)) {
    delay(200);
    if (detectTouch(box * 1, box * 3.5, box * 4, box * 1.5)) {
      playerChoice = 2;
      if (aiChoice == 3) {
        tft.setTextColor(ILI9341_GREEN);
        tft.setTextSize(1);
        tft.setCursor(box * 0, box * 7);
        tft.print("AI had scissors. You lose!");
        delay(5000);
        tft.fillScreen(ILI9341_BLACK);
        drawButton();
        delay(2000);
        drawScreen();
        
      } else if (aiChoice == 2) {
        tft.setTextColor(ILI9341_GREEN);
        tft.setTextSize(1);
        tft.setCursor(box * 0, box * 7);
        tft.print("AI had paper. Tie!");
        delay(5000);
        tft.fillScreen(ILI9341_BLACK);
        drawButton();
        delay(2000);
        drawScreen();
        
      } else {
        tft.setTextColor(ILI9341_GREEN);
        tft.setTextSize(1);
        tft.setCursor(box * 0, box * 7);
        tft.print("AI had rock. You win!");
        delay(5000);
        tft.fillScreen(ILI9341_BLACK);
        drawButton();
        delay(2000);
        drawScreen();
        
      }}

    }
    delay(10);
    if (detectTouch(box * 1, box * 5.2, box * 4, box * 1.5)) {
      delay(200);
      if (detectTouch(box * 1, box * 5.2, box * 4, box * 1.5)) {
        playerChoice = 3;
        if (aiChoice == 1) {
          tft.setTextColor(ILI9341_GREEN);
          tft.setTextSize(1);
          tft.setCursor(box * 0, box * 7);
          tft.print("AI had rock. You lose!");
          delay(5000);
          tft.fillScreen(ILI9341_BLACK);
          drawButton();
          delay(2000);
          drawScreen();
        
        } else if (aiChoice == 3) {
          tft.setTextColor(ILI9341_GREEN);
          tft.setTextSize(1);
          tft.setCursor(box * 0, box * 7);
          tft.print("AI had scissors. Tie");
          delay(5000);
          tft.fillScreen(ILI9341_BLACK);
          drawButton();
          delay(2000);
          drawScreen();
        
        } else {
          tft.setTextColor(ILI9341_GREEN);
          tft.setTextSize(1);
          tft.setCursor(box * 0, box * 7);
          tft.print("AI had paper. You win!");
          delay(5000);
          tft.fillScreen(ILI9341_BLACK);
          drawButton();
          delay(2000);
          drawScreen();
        }
      }
    }
 
  yield();

}

void drawScreen() {
  tft.fillScreen(ILI9341_BLACK);
  tft.setCursor(box * 1, box * 1);
  tft.setTextSize(2);
  tft.print("Choose");
  //rock
  drawBox(" ", box * 1, box * 1.8);
  tft.drawRGBBitmap(box * 1, box * 1.8, rock, 80, 40);
  //paper
  drawBox(" ", box * 1, box * 3.5);
  tft.drawRGBBitmap(box * 1, box * 3.5, paper, 80, 40);

  //scissors
  drawBox(" ", box * 1, box * 5.2);
  tft.drawRGBBitmap(box * 1, box * 5.2, scissor, 80, 40);
  yield();
  while (1) {

    AI();
    delay(20);
  }
}

void setup() {
  Serial.begin(115200);
  ts.begin();
  tft.begin();
  tft.fillScreen(ILI9341_BLACK);
  drawButton();
  delay(5000);
  //      Clear Screen
  drawScreen();
}



void loop() {

}
