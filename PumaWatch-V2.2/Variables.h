#include <Wire.h>
#include <Tone32.h>
#include <BMP180.h>
#include <SimpleKalmanFilter.h>
#include <TinyGPS++.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <SPI.h>
#include <TFT_eSPI.h>
#include <TFT_eFEX.h>              // Include the extension graphics functions library
#define FS_NO_GLOBALS
#include <FS.h>

#ifdef ESP32
#include "SPIFFS.h" // Needed for ESP32 only
#endif




BMP180 baro;
SimpleKalmanFilter Baro(0.1, 0.02, 0.01);
SimpleKalmanFilter Vario(0.1, 0.02, 0.01);
TinyGPSPlus gps;
TFT_eSPI tft = TFT_eSPI();   // Invoke library
TFT_eFEX  fex = TFT_eFEX(&tft);    // Create TFT_eFX object "efx" with pointer to "tft" object


void GetSketchName(){
  
    String path = __FILE__;
    int slash = path.lastIndexOf('\x5C');
    String the_cpp_name = path.substring(slash+1);
    int dot_loc = the_cpp_name.lastIndexOf('.');
    String Firmware = the_cpp_name.substring(0, dot_loc);
    Serial.println(Firmware);
    
}
