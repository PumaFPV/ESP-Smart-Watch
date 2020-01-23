#include <TinyGPS++.h>

TinyGPSPlus gps;  

int totalTrip, previousTotalTrip, previousGPSLat, previousGPSLng;
int currentAlt, previousAlt, previousUpHill, currentUpHill;
int minGPSSpeed, maxGPSSpeed, avgGPSSpeed, previousAvgGPSSpeed, currentGPSSpeed;
int gpsSecond, gpsMinute, gpsHour, gpsDay, gpsMonth, gpsYear;
String Day, Month;

void TotalDistance(){
  totalTrip = previousTotalTrip + TinyGPSPlus::distanceBetween(gps.location.lat(), gps.location.lng(), previousGPSLat, previousGPSLng);
  previousTotalTrip = totalTrip;
  previousGPSLat = gps.location.lat();
  previousGPSLng = gps.location.lng();
}

void UpHill(){
  currentAlt = gps.altitude.meters();
  if(currentAlt > previousAlt){
    currentUpHill = previousUpHill + (currentAlt - previousAlt);
    previousUpHill = currentUpHill;
  }
  previousAlt = currentAlt;
}

void GPSSpeed(){
  if(minGPSSpeed > gps.speed.mps()){
    minGPSSpeed = gps.speed.mps();
  }
  if(maxGPSSpeed < gps.speed.mps()){
    maxGPSSpeed = gps.speed.mps();
  }
  avgGPSSpeed = (previousAvgGPSSpeed + gps.speed.mps()) / 2;
  previousAvgGPSSpeed = avgGPSSpeed;
  currentGPSSpeed = gps.speed.mps();
}

void GPSClock(){
  gpsSecond = gps.time.second();
  gpsMinute = gps.time.minute();
  gpsHour   = gps.time.hour();
  gpsDay    = gps.date.day();
  gpsMonth  = gps.date.month();
  gpsYear   = gps.date.year();  

  String Time = (String)gps.time.hour() + " " + (String)gps.time.minute() + " " + (String)gps.time.second();


  switch(gpsMonth){
    case 1:
      Month = "Janvier";
      break;
    case 2:
      Month = "Février";
      break;
    case 3:
      Month = "Mars";
      break;
    case 4:
      Month = "Avril";
      break;
    case 5:
      Month = "Mai";
      break;
    case 6:
      Month = "Juin";
      break;
    case 7:
      Month = "Juillet";
      break;    
    case 8:
      Month = "Août";
      break;
    case 9:
      Month = "Septembre";
      break;
    case 10:
      Month = "Octobre";
      break;
    case 11:
      Month = "Novembre";
      break;
    case 12:
      Month = "Décembre";
      break;  
  }
  String Date = (String)gps.date.day() + "  " + Month + " " + (String)gps.date.year();
     
}


void setup(){
  Serial.begin(115200);
  Serial2.begin(9600);
}

void loop(){
      Serial.println(gps.satellites.value());
  if(gps.satellites.value() > 4){
    TotalDistance(); 
    UpHill(); 
    GPSSpeed(); 
    GPSClock();
  }
}
