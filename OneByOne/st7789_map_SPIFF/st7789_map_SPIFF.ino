
#define FS_NO_GLOBALS
#include <FS.h>

#ifdef ESP32
#include "SPIFFS.h" // Needed for ESP32 only
#endif

#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();   // Invoke library

#include <TFT_eFEX.h>              // Include the extension graphics functions library
TFT_eFEX  fex = TFT_eFEX(&tft);    // Create TFT_eFX object "efx" with pointer to "tft" object

int x, y = 0;
bool translate = 0; //0 = x, 1 = y


void setup(void) {
  Serial.begin(115200);
  Serial.print("ST7789 TFT SPIFF JPG Test");

  tft.begin();     // initialize a ST7789 chip
  tft.setSwapBytes(true); // Swap the byte order for pushImage() - corrects endianness
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(3);
  tft.setTextDatum(MC_DATUM);
  
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);

  
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield(); // Stay here twiddling thumbs waiting
  }
  
  fex.listSPIFFS(); // Lists the files so you can see what is in the SPIFFS

}

void loop() {
/*
    tft.pushImage(x,       y,       240, 240, zoom1);
    tft.pushImage(x + 240, y,       240, 240, zoom2);
    tft.pushImage(x + 480, y,       240, 240, zoom3);
    
    tft.pushImage(x,       y + 240, 240, 240, zoom4);
    tft.pushImage(x + 240, y + 240, 240, 240, zoom5);
    tft.pushImage(x + 480, y + 240, 240, 240, zoom6);
    
    tft.pushImage(x,       y + 480, 240, 230, zoom7);
    tft.pushImage(x + 240, y + 480, 240, 230, zoom8);
    tft.pushImage(x + 480, y + 480, 240, 230, zoom9);
*/


fex.drawJpgFile(SPIFFS, "/veyrier.jpg", 0, 0, 240, 240, x, y, (jpeg_div_t)JPEG_DIV_NONE);
Serial.println("Coordinates " + (String)x + "  " + (String)y);
/*
fex.drawJpgFile(SPIFFS, "/zoom1.jpg", 0, 0, 240, 240, x,       y      );
fex.drawJpgFile(SPIFFS, "/zoom2.jpg", 0, 0, 240, 240, x + 240, y      );
fex.drawJpgFile(SPIFFS, "/zoom3.jpg", 0, 0, 240, 240, x + 480, y      );
fex.drawJpgFile(SPIFFS, "/zoom4.jpg", 0, 0, 240, 240, x      , y + 240);
fex.drawJpgFile(SPIFFS, "/zoom5.jpg", 0, 0, 240, 240, x + 240, y + 240);
fex.drawJpgFile(SPIFFS, "/zoom6.jpg", 0, 0, 240, 240, x + 480, y + 240);
fex.drawJpgFile(SPIFFS, "/zoom7.jpg", 0, 0, 240, 240, x      , y + 480);
fex.drawJpgFile(SPIFFS, "/zoom8.jpg", 0, 0, 240, 240, x + 240, y + 480);
fex.drawJpgFile(SPIFFS, "/zoom9.jpg", 0, 0, 240, 240, x + 480, y + 480);
*/
    if(translate == 0){
      tft.drawString("X", 0, 240);
    }else{
      tft.drawString("Y", 0, 240);
    }

if(digitalRead(26) == LOW && translate == 0){
  translate = 1;
  delay(50);
}
if(digitalRead(26) == LOW && translate == 1){
  translate = 0;
  tft.drawString("x", 0, 240);
  delay(50);
}

if(digitalRead(27) == LOW && translate == 0){
  x--;
}
if(digitalRead(25) == LOW && translate == 0){
  x++;
}
if(digitalRead(27) == LOW && translate == 1){
  y--;
}
if(digitalRead(25) == LOW && translate == 1){
  y++;
}

      
  
}
