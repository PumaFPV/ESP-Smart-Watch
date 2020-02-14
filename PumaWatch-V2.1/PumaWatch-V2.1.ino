#define VARIO_PWR false     //Turn on vario code
#define VARIO_DEBUG false  //Turn on Vario serial output
#define CARDIO_DEBUG true //Turn on Cardio serial output
#define GPS_DEBUG false    //Turn on GPS serial output



#include "Variables.h"

#include "varioFile.h"
#include "cardioFile.h"
#include "gpsFile.h"
#include "sdFile.h"


void setup(){
Serial.begin(115200);
setupCardio();

}


void loop(){
loopCardio();
}
