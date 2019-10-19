#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <SFE_BMP180.h>
#include <TinyGPS++.h>
#include <SimpleKalmanFilter.h>
//#include <MAX30105.h>
//#include "heartrate.h" 



SimpleKalmanFilter pressureKalmanFilter(0.1, 0.02, 0.01);
U8G2_SSD1306_64X48_ER_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
TinyGPSPlus gps;
//MAX30105 heartratesensor;
SFE_BMP180 bmp;

//---------------------------------------------BMP---------------------------------------------
const long SERIAL_REFRESH_TIME = 100;
long refresh_time;

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


//---------------------------------------------Cardio---------------------------------------------
/*
const byte RATE_SIZE = 4;
byte rates[RATE_SIZE];
byte rateSpot = 0;
long lastBeat = 0;
float beatsPerMinute;
int beatAvg;
*/

//---------------------------------------------GPS---------------------------------------------
int totalTrip, previousTotalTrip, previousGPSLat, previousGPSLng;
int currentAlt, previousAlt, previousUpHill, currentUpHill;
int minGPSSpeed, maxGPSSpeed, avgGPSSpeed, previousAvgGPSSpeed, currentGPSSpeed;
int gpsSecond, gpsMinute, gpsHour, gpsDay, gpsMonth, gpsYear;


//---------------------------------------------SETUP---------------------------------------------
void setup(){
  Serial.begin(115200);

  // BMP180 Pressure sensor start
  if (!bmp.begin()) {
    Serial.println("BMP180 Pressure Sensor Error!");
    while(1); // Pause forever.
  }
  baseline = getPressure();


  /*  
  heartratesensor.setup();
  heartratesensor.setPulseAmplitudeRed(0x0A);
  heartratesensor.setPulseAmplitudeGreen(0);
 */


  u8g2.begin();

}


//---------------------------------------------LOOP---------------------------------------------
void loop(){
   float p = getPressure();
  float altitude = bmp.altitude(p,baseline);
  float estimated_altitude = pressureKalmanFilter.updateEstimate(altitude);


  

   /*
  long irValue = heartratesensor.getIR();

  if (checkForBeat(irValue) == true){
    
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20){
      
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
      
    }
    
  }
*/

  if(gps.satellites.value() > 4){

  totalTrip = previousTotalTrip + TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), previousGPSLat, previousGPSLng);
  previousTotalTrip = totalTrip;
  previousGPSLat = gps.location.lat();
  previousGPSLng = gps.location.lng();

  currentAlt = gps.altitude.meters();
  if(currentAlt > previousAlt){
    currentUpHill = previousUpHill + (currentAlt - previousAlt);
    previousUpHill = currentUpHill;
  }
  previousAlt = currentAlt;


  if(minGPSSpeed > gps.speed.mps()){
    minGPSSpeed = gps.speed.mps();
  }
  if(maxGPSSpeed < gps.speed.mps()){
    maxGPSSpeed = gps.speed.mps();
  }
  avgGPSSpeed = (previousAvgGPSSpeed + gps.speed.mps()) / 2;
  previousAvgGPSSpeed = avgGPSSpeed;
  currentGPSSpeed = gps.speed.mps();

  gpsSecond = gps.time.second();
  gpsMinute = gps.time.minute();
  gpsHour   = gps.time.hour();
  gpsDay    = gps.date.day();
  gpsMonth  = gps.date.month();
  gpsYear   = gps.date.year();  
    
  }




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
