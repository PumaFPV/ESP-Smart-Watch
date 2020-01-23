#include <Wire.h>
#include <Tone32.h>
#include <BMP180.h>
#include <SimpleKalmanFilter.h>
#include <TinyGPS++.h>


BMP180 baro;
SimpleKalmanFilter Baro(0.1, 0.02, 0.01);
SimpleKalmanFilter Vario(0.1, 0.02, 0.01);
TinyGPSPlus gps;
