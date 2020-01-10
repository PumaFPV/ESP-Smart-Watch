#include <Wire.h>
#include <Tone32.h>
#include <BMP180.h>
#include <SimpleKalmanFilter.h>

BMP180 baro;
SimpleKalmanFilter Baro(0.1, 0.02, 0.01);
SimpleKalmanFilter Vario(0.1, 0.02, 0.01);

#define VARIO_PWR true
#define BUZZER_PIN 33
#define DEBUG_VARIO true
#define VARIO_BEEP true
#define MIN_SCHRESHOLD -90  //in cm
#define MAX_SCHRESHOLD 80 //in cm
#define MIN_VARIO -1000 //in cm
#define MAX_VARIO 1000  //in cm
#define MIN_FREQ  200
#define MAX_FREQ  1800
#define MIN_TIME  2000
#define MAX_TIME  100

float baseline; // baseline pressure
int VarioFreq, VarioTime;
float deltaAlt = 0.00;  


void setup() {
  Wire.begin();
  Serial.begin(115200);
  baro.begin();

  tone(BUZZER_PIN, 440, 1000, 0);
  tone(BUZZER_PIN, 880, 500, 0);
  noTone(BUZZER_PIN);

}

void loop(){
  if(VARIO_PWR){
    baro.read();
    float estimated_altitude = Baro.updateEstimate(baro.alti);

    delay(100);
    deltaAlt = Baro.updateEstimate(baro.alti) - estimated_altitude;  
    float estimated_Vario = Vario.updateEstimate(deltaAlt * 100) * 100;
    
    VarioFreq = constrain(map(estimated_Vario, MIN_VARIO, MAX_VARIO, MIN_FREQ, MAX_FREQ), 0, 16000);
    VarioTime = constrain(map(estimated_Vario, MIN_VARIO, MAX_VARIO, MIN_FREQ, MAX_TIME), 0, 2000);

    if((estimated_Vario < MIN_SCHRESHOLD || MAX_SCHRESHOLD < estimated_Vario) && VARIO_BEEP){
      tone(BUZZER_PIN, VarioFreq, VarioTime, 0);
      noTone(BUZZER_PIN);  
    }
      
    if(DEBUG_VARIO){
      Serial.print(baro.alti);
      Serial.print("  ");
      Serial.print(estimated_altitude);
      Serial.print("  ");
      Serial.print(estimated_Vario/100);
      Serial.print("  ");
      //Serial.print(VarioFreq);
      Serial.print("    ");
      //Serial.print(VarioTime);
      Serial.println();     
    }
  }
}
