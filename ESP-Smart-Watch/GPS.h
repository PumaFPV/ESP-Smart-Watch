

int totalTrip, previousTotalTrip, previousGPSLat, previousGPSLng;
int currentAlt, previousAlt, previousUpHill, currentUpHill;
int minGPSSpeed, maxGPSSpeed, avgGPSSpeed, previousAvgGPSSpeed, currentGPSSpeed;
int gpsSecond, gpsMinute, gpsHour, gpsDay, gpsMonth, gpsYear;


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
}

void GPSLoop(){
  if(gps.satellites.value() > 4){
    TotalDistance(); UpHill(); GPSSpeed(); GPSClock();
  }
}
