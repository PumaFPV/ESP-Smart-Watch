#define BuzzerPin 1

#define minVario  -5
#define maxVario  5
#define minFreq 100
#define maxFreq 12000
#define minTime 100
#define maxTime 2000
#define IntervalOneSec 1000
#define IntervalNeutral 5000  

int VarioOneSec, VarioNeutral = 0;
unsigned long PreviousMillisOneSec, PreviousMillisNeutral = 0;
int cycle = 0;
int SumAlti = 0;
int AverageAlti = 0;


void BaroSetup(){
  
  bmp180.begin();
  
}


void GetData(){
  if(bmp180.read()){
    //Serial.println((String) "Pression= " + bmp.pres + "     Temperature= " + bmp.temp + "      Altitude= " + bmp.alti);
    //Serial.println(bmp.alti);
  }
  else{
    Serial.println("Pas de données capteur");
  }
}

void ProcessData(){
  
  int CurrentAltitude = bmp180.alti;
  unsigned long CurrentMillis = millis();

  /*
  if(CurrentMillis - PreviousMillisOneSec >= IntervalOneSec){
    PreviousMillisOneSec = CurrentMillis;

    int RealVarioOneSec = CurrentAltitude - bmp.alti;
    VarioOneSec = constrain(RealVarioOneSec, minVario, maxVario);
    Serial.print(VarioOneSec);
  }

  if(CurrentMillis - PreviousMillisNeutral >= IntervalNeutral){
    PreviousMillisNeutral = CurrentMillis;

    int RealVarioNeutral = CurrentAltitude- bmp.alti;
    VarioNeutral = constrain(RealVarioNeutral, minVario, maxVario);
    Serial.print(VarioNeutral);
  }*/

  for(int i = 0; i < 60; i++){
    SumAlti = SumAlti + bmp180.alti; 
  }
  AverageAlti = SumAlti/60;
  Serial.print(bmp180.alti);
  Serial.print("      ");
  Serial.println(AverageAlti);
}

void OutputBuzzer(){
  int BuzzerFreq = map(VarioOneSec, minVario, maxVario, minFreq, maxFreq);
  int BuzzerTime = map(VarioOneSec, minVario, maxVario, maxTime, minTime);
  //tone(BuzzerPin, BuzzerFreq, BuzzerTime);  
}


void BaroLoop(){
  
  GetData();
  ProcessData();
  OutputBuzzer();
  
}
