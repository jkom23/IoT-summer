#include <SPI.h>
#include "ILI9341_SPI.h"
#include <MiniGrafx.h>
#include "fonts.h"
#include "sunicon.h"
//pinout for lcd screen and touchscreen
#define STMPE_CS 16
#define TFT_CS 0
#define TFT_DC 15
#define SD_CS 2
#define TFT_LED 5

//custom color palette
#define BLACK_COLOR 0x0000
#define WHITE_COLOR 0xFFFF
#define GREEN_COLOR 0x07E2
#define PURPLE_COLOR 0xB81F

int BITS_PER_PIXEL = 2; //2 ^ 2 colors

uint16_t palette[] = {
  BLACK_COLOR, //0
  WHITE_COLOR, //1
  GREEN_COLOR, //2
  PURPLE_COLOR, //3
};

//screen and gfx library initialization
ILI9341_SPI tft = ILI9341_SPI(TFT_CS, TFT_DC);
MiniGrafx gfx = MiniGrafx(&tft, BITS_PER_PIXEL, palette);

void powerOn() {
  pinMode(TFT_LED, OUTPUT);
  digitalWrite(TFT_LED, HIGH);
}

void displayTFT() {
  gfx.setColor(2);
  gfx.drawLine(10, 20, 40, 30);
  gfx.setColor(3);
  gfx.drawCircle(120, 160, 118);
  gfx.setColor(2);
  gfx.drawHorizontalLine(30, 30, 90);
  gfx.drawVerticalLine(90, 30, 90);
  //gfx.setTextAlignment(TEXT_ALIGN_CENTER);
  gfx.setFont(Open_Sans_Condensed_Bold_16);
  gfx.drawString(100, 10, "Hello");
  gfx.fillRect(60, 60, 60, 60);
  gfx.drawPalettedBitmapFromPgm(120, 160, sunicon);
  gfx.commit();

}

void screenSet() {
  gfx.init();
  gfx.fillBuffer(0);
}

void setup() {
  // put your setup code here, to run once:
  //power on screen
  powerOn();
  screenSet();
  gfx.commit();
  displayTFT();

}

void loop() {
  // put your main code here, to run repeatedly:

}
