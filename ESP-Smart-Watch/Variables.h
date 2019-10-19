#ifndef Variables_h
#define Variables_h

#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <SFE_BMP180.h>
#include <TinyGPS++.h>
#include <SimpleKalmanFilter.h>
#include <MAX30105.h>
#include "heartrate.h"

SimpleKalmanFilter pressureKalmanFilter(0.1, 0.02, 0.01);
U8G2_SSD1306_64X48_ER_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
TinyGPSPlus gps;
MAX30105 heartratesensor;
SFE_BMP180 bmp;

#endif
