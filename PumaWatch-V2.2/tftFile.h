void setupTFT(){
  tft.begin(),
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.fillCircle(120, 120, 120, brightness(TFT_WHITE, 50));
}
