//#include <SimpleKalmanFilter.h>
//#include <SFE_BMP180.h>


/*
 This sample code demonstrates how the SimpleKalmanFilter object can be used with a
 pressure sensor to smooth a set of altitude measurements. 
 This example needs a BMP180 barometric sensor as a data source.
 https://www.sparkfun.com/products/11824

 SimpleKalmanFilter(e_mea, e_est, q);
 e_mea: Measurement Uncertainty 
 e_est: Estimation Uncertainty 
 q: Process Noise
 */


// Serial output refresh time
const long BSERIAL_REFRESH_TIME = 100;
long Brefresh_time;

float baseline; // baseline pressure

double getPressure() {
  char status;
  double T,P;
  status = bmp.startTemperature();
  if (status != 0) {
    delay(status);
    status = bmp.getTemperature(T);
    if (status != 0) {
      status = bmp.startPressure(3);
      if (status != 0) {
        delay(status);
        status = bmp.getPressure(P,T);
        if (status != 0) {
          return(P);
        }
      } 
    }  
  } 
}


void Baroloop() {
  
  float p = getPressure();
  float altitude = bmp.altitude(p,baseline);
  float estimated_altitude = pressureKalmanFilter.updateEstimate(altitude);

  if (millis() > Brefresh_time) {
    Serial.print(altitude,6);
    Serial.print(",");
    Serial.print(estimated_altitude,6);
    Serial.println();
    Brefresh_time = millis()+ 100;
  }
  
}
