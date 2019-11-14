void ScreenSetup(){
  
  u8g2.begin();

}



void ScreenLoop(){
  
  if (millis() > refresh_time) {
    Serial.print(estimated_altitude,6);
    Serial.println();
    refresh_time = millis() + SERIAL_REFRESH_TIME;

     u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB14_tr);
    u8g2.setCursor(0, 20);
    u8g2.print(estimated_altitude);
  } 
  while ( 
    u8g2.nextPage() 
  );
    
  }
}
