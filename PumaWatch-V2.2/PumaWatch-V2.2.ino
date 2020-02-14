// #########################################################################
// Serial output debug options
// #########################################################################
#define VARIO_PWR true     //Turn on vario code
#define VARIO_DEBUG true  //Turn on Vario serial output
#define CARDIO_DEBUG false //Turn on Cardio serial output
#define GPS_DEBUG false    //Turn on GPS serial output



// #########################################################################
// Include non dependant files
// #########################################################################
#include "variables.h"
#include "graphics.h"



// #########################################################################
// Include main lib files
// #########################################################################
#include "tftFile.h"
#include "varioFile.h"
#include "cardioFile.h"
#include "gpsFile.h"
#include "sdFile.h"



// #########################################################################
// Include lib dependant files
// #########################################################################
#include "kml.h"
#include "map.h"


// #################################################################################################################################
// void setup
// #################################################################################################################################
void setup(){
  
  Serial.begin(115200);

  GetSketchName()
  
  setupTFT();
  setupCardio();
  setupVario();

}



// #################################################################################################################################
// void loop
// #################################################################################################################################
void loop(){

  loopVario();
  loopCardio();

  int varioOut = map(estimated_Vario/100, -10, 10, -90, 90);
  roundedArc(120, 120, 105, 10, 90, varioOut, TFT_CYAN);
  delay(200);

}
