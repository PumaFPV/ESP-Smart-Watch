/*#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <SFE_BMP180.h>
#include <TinyGPS++.h>
#include <SimpleKalmanFilter.h>
#include <MAX30105.h>
#include "heartrate.h" */



#include "Variables.h"

#include "GPS.h"
#include "Barometer.h"
#include "CLock.h"
#include "Cardio.h"
#include "OLED.h"



void setup(){
  BaroSetup();
  HeartBeatSetup();
  KalmanSetup();
   
}

void loop(){
  
  ScreenLoop();
  GPSLoop();
  KalmanLoop();
  HeartBeatLoop();
  
}
