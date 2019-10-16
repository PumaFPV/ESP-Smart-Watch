const long SERIAL_REFRESH_TIME = 100;
long refresh_time;

float baseline; // baseline pressure

void KalmanSetup() {

  baseline = getPressure();
 
}

void KalmanLoop() {
  
  float p = getPressure;
  float altitude = pressure.altitude(p,baseline);
  float estimated_altitude = pressureKalmanFilter.updateEstimate(altitude);
  
}
