// #########################################################################
// GPS file
// #########################################################################
/*  Tiny GPS library commands
 * Number of sattelites: gps.satellites.value() gps.satellites.isValid()
 * Latitude:  gps.location.lat()  gps.location.isValid()
 * Longitude: gps.location.lat()  
 * Altitude: gps.altitude.meters()  gps.altitude.isValid
 * Speed: gps.speed.kmph()  gps.speed.isValid()
 * Distance between:TinyGPS::distanceBetween(lat1, lng1, lat2, lng2)
 * Date: gps.date
 * Time: gps.time
 * 
 */



// #########################################################################
// Initialise GPS variables
// #########################################################################
float ARGENTIERE_LAT = 45.974567, ARGENTIERE_LON = 06.920673;



// #########################################################################
// Initialise GPS void
// #########################################################################
static void smartDelay(unsigned long ms);
static void printFloat(float val, bool valid, int len, int prec);
static void printInt(unsigned long val, bool valid, int len);
static void printStr(const char *str, int len);
static void printDateTime(TinyGPSDate &d, TinyGPSTime &t);


// #########################################################################
// setup GPS
// #########################################################################
void setupGPS(){
  
  Serial2.begin(9600);

  if(GPS_DEBUG){
    Serial.println(F("Sats HDOP  Latitude   Longitude   Fix  Date       Time     Date Alt    Course Speed Card  Distance Course Card  Chars Sentences Checksum"));
    Serial.println(F("           (deg)      (deg)       Age                      Age  (m)    --- from GPS ----  ---- to London  ----  RX    RX        Fail"));
    Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------------"));
  }
  
}



// #########################################################################
// loop GPS
// #########################################################################
void loopGPS(){
    
  if(GPS_DEBUG){
    printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
    printFloat(gps.hdop.hdop(), gps.hdop.isValid(), 6, 1);
    printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
    printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
    printInt(gps.location.age(), gps.location.isValid(), 5);
    printDateTime(gps.date, gps.time);
    printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
    printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
    printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
    printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.deg()) : "*** ", 6);
  
    unsigned long distanceKmToLondon =
      (unsigned long)TinyGPSPlus::distanceBetween(
        gps.location.lat(),
        gps.location.lng(),
        ARGENTIERE_LAT, 
        ARGENTIERE_LON) / 1000;
    printInt(distanceKmToLondon, gps.location.isValid(), 9);

    double courseToLondon =
      TinyGPSPlus::courseTo(
        gps.location.lat(),
        gps.location.lng(),
        ARGENTIERE_LAT, 
        ARGENTIERE_LON);

    printFloat(courseToLondon, gps.location.isValid(), 7, 2);

    const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);

    printStr(gps.location.isValid() ? cardinalToLondon : "*** ", 6);

    printInt(gps.charsProcessed(), true, 6);
    printInt(gps.sentencesWithFix(), true, 10);
    printInt(gps.failedChecksum(), true, 9);
    Serial.println();
    
    smartDelay(1000);
    
  }

}
  


// #########################################################################
// Smart delay
// #########################################################################
static void smartDelay(unsigned long ms){
  
  unsigned long start = millis();
  
  do{
    while (Serial2.available())
      gps.encode(Serial2.read());
  } while (millis() - start < ms);
}



// #########################################################################
// print float
// #########################################################################
static void printFloat(float val, bool valid, int len, int prec){
  
  if (!valid){
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }else{
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  
  smartDelay(0);
  
}



// #########################################################################
// Print int
// #########################################################################
static void printInt(unsigned long val, bool valid, int len){
  
  char sz[32] = "*****************";
  
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
  
}



// #########################################################################
// print DateTime
// #########################################################################
static void printDateTime(TinyGPSDate &d, TinyGPSTime &t){  
  
  if (!d.isValid()){
    Serial.print(F("********** "));
  }else{
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid()){
    Serial.print(F("******** "));
  }else{
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
  
}



// #########################################################################
// Print string
// #########################################################################
static void printStr(const char *str, int len){
  
  int slen = strlen(str);
  
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);

}
