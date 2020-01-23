#define VARIO_PWR true     //Turn on vario code
#define VARIO_DEBUG false  //Turn on Vario serial output
#define CARDIO_DEBUG false //Turn on Cardio serial output
#define GPS_DEBUG false    //Turn on GPS serial output

#include "Variables.h"

#include "Vario.h"
#include "Cardio.h"
#include "GPS.h"


TaskHandle_t VarioCore;
TaskHandle_t CardioCore;
TaskHandle_t GPSCore;


void setup(){
    xTaskCreatePinnedToCore(VarioCode,  "VarioCore",  1024, NULL, 1, NULL, 1); //void name, Task name, Stack size, parameter as input, priority, task handle, core
    xTaskCreatePinnedToCore(CardioCode, "CardioCore", 1024, NULL, 1, NULL, 1);
    xTaskCreatePinnedToCore(GPSCode,    "GPSCore",    2048, NULL, 1, NULL, 1);
}






















void loop(){}
