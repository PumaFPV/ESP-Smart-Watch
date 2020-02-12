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
