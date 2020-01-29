#include <TFT_eSPI.h>
#include "bitmap.h" 
TFT_eSPI tft = TFT_eSPI();   // Invoke library

int x, y = 0;
bool translate = 0; //0 = x, 1 = y


void setup(void) {
  Serial.begin(115200);
  Serial.print("ST7789 TFT Bitmap Test");

  tft.begin();     // initialize a ST7789 chip
  tft.setSwapBytes(true); // Swap the byte order for pushImage() - corrects endianness
  tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(3);
  tft.setTextDatum(MC_DATUM);
  
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);

}

void loop() {
  
    tft.pushImage(x,       y,       240, 240, zoom1);
    tft.pushImage(x + 240, y,       240, 240, zoom2);
    //tft.pushImage(x + 480, y,       240, 240, zoom3);
    
    tft.pushImage(x,       y + 240, 240, 240, zoom4);
    tft.pushImage(x + 240, y + 240, 240, 240, zoom5);
    tft.pushImage(x + 480, y + 240, 240, 240, zoom6);
    
    //tft.pushImage(x,       y + 480, 240, 230, zoom7);
    tft.pushImage(x + 240, y + 480, 240, 230, zoom8);
    tft.pushImage(x + 480, y + 480, 240, 230, zoom9);
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
