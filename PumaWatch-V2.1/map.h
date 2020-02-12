int x, y = 0;
bool translate = 0; //0 = x, 1 = y


void mapSetup() {
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

void mapLoop() {

  for(int i = 0; i<960; i++){
    unsigned long nowTime = millis();
    fex.drawJpgFile(SPIFFS, "/veyrier.jpg", 0, 0, 480, 480, 0, i, (jpeg_div_t)JPEG_DIV_2); //JPEG_DIV_2 4 8 MAX
    Serial.println(millis() - nowTime);
  }
  Serial.println("Coordinates " + (String)x + "  " + (String)y);

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
