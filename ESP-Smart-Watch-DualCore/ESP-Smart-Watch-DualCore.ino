#include <Wire.h>
#include <Tone32.h>
#include <BMP180.h>
#include <SimpleKalmanFilter.h>

BMP180 baro;
SimpleKalmanFilter KFBaro(0.1, 0.02, 0.01); //0.1, 0.02, 0.01 those values seem to work fine by now
SimpleKalmanFilter KFVario(10, 6, 1); //10, 6, 1 those values seem to work fine by now

TaskHandle_t Vario;

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

void setup(){
  Wire.begin();
  Serial.begin(115200);
  baro.begin();

//xTaskCreatePinnedToCore(Function, Task name, Stack size, parameter as input, priority 3 highest, task handle, core0 = wifi);
  xTaskCreatePinnedToCore(VarioCode, "Vario", 1024, NULL, 3, NULL, 1); //Function, Task name, Stack size, parameter as input, priority 3 highest, task handle, core (0 = wifi)


}


//--------------------------------------------------VARIO-CODE--------------------------------------------------
void VarioCode(void *pvParameters){
//--------------------------------------------------VARIO-SETUP--------------------------------------------------  

  
//--------------------------------------------------VARIO-LOOP-------------------------------------------------- 
  for(;;){    //tone(BUZZER_PIN, freq, time, 0);

    if(VARIO_PWR){
      baro.read();
      float prevAltitude = KFBaro.updateEstimate(baro.alti);

    vTaskDelay(100);
    deltaAlt = KFBaro.updateEstimate(baro.alti) - prevAltitude;  
    float estimated_Vario = KFVario.updateEstimate(deltaAlt * 100) * 100;
    
    VarioFreq = constrain(map(estimated_Vario, MIN_VARIO, MAX_VARIO, MIN_FREQ, MAX_FREQ), 0, 16000);
    VarioTime = constrain(map(estimated_Vario, MIN_VARIO, MAX_VARIO, MIN_FREQ, MAX_TIME), 0, 2000);

    if((estimated_Vario < MIN_SCHRESHOLD || MAX_SCHRESHOLD < estimated_Vario) && VARIO_BEEP){
      tone(BUZZER_PIN, VarioFreq, VarioTime, 0);
      noTone(BUZZER_PIN);  
    }
      
    if(DEBUG_VARIO){
      Serial.print(baro.alti);
      Serial.print("  ");
      Serial.print(KFBaro.updateEstimate(baro.alti));
      Serial.print("  ");
      Serial.print(estimated_Vario/100);
      Serial.print("  ");
      //Serial.print(VarioFreq);
      Serial.print("    ");
      //Serial.print(VarioTime);
      Serial.println();     
    }
  }
  
  }//----------VARIO-LOOP-END
  
}



void loop(){}
