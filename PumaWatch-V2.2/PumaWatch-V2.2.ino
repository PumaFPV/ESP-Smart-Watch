#define VARIO_PWR true     //Turn on vario code
#define VARIO_DEBUG true  //Turn on Vario serial output
#define CARDIO_DEBUG false //Turn on Cardio serial output
#define GPS_DEBUG false    //Turn on GPS serial output



#include "Variables.h"

#include "varioFile.h"
#include "cardioFile.h"
#include "gpsFile.h"
#include "sdFile.h"

#define DEG2RAD 0.0174532925

#define LOOP_DELAY 10 // Loop delay to slow things down


byte inc = 0;
unsigned int col = 0;
double pi = 3.14159265359;
byte red = 31; // Red is the top 5 bits of a 16 bit colour value
byte green = 0;// Green is the middle 6 bits
byte blue = 0; // Blue is the bottom 5 bits
byte state = 0;


int fillArc(int x, int y, int start_angle, int seg_count, int rx, int ry, int w, unsigned int colour){

  byte seg = 1; // Segments are 3 degrees wide = 120 segments for 360 degrees
  byte inc = 6; // Draw segments every 3 degrees, increase to 6 for segmented ring

  // Calculate first pair of coordinates for segment start
  float sx = cos((start_angle - 90) * DEG2RAD);
  float sy = sin((start_angle - 90) * DEG2RAD);
  uint16_t x0 = sx * (rx - w) + x;
  uint16_t y0 = sy * (ry - w) + y;
  uint16_t x1 = sx * rx + x;
  uint16_t y1 = sy * ry + y;

  // Draw colour blocks every inc degrees
  for (int i = start_angle; i < start_angle + seg * seg_count; i += inc) {

    // Calculate pair of coordinates for segment end
    float sx2 = cos((i + seg - 90) * DEG2RAD);
    float sy2 = sin((i + seg - 90) * DEG2RAD);
    int x2 = sx2 * (rx - w) + x;
    int y2 = sy2 * (ry - w) + y;
    int x3 = sx2 * rx + x;
    int y3 = sy2 * ry + y;

    tft.fillTriangle(x0, y0, x1, y1, x2, y2, colour);
    tft.fillTriangle(x1, y1, x2, y2, x3, y3, colour);

    // Copy segment end to sgement start for next segment
    x0 = x2;
    y0 = y2;
    x1 = x3;
    y1 = y3;
  }
}


int roundedArc(int x, int y, int r, int w, int startingAngle, int angle, int color){
  fillArc(x, y, startingAngle, angle, r, r, w, color);
  tft.fillCircle(x - (r - w / 2) * sin(startingAngle * DEG2RAD),           y - (r - w / 2) * cos(startingAngle * DEG2RAD),           w/2, color);
  tft.fillCircle(x + (r - w / 2) * sin((startingAngle + angle ) * DEG2RAD), y - (r - w / 2) * cos((startingAngle + angle) * DEG2RAD), w/2, color);  
}



// #########################################################################
// Return the 16 bit colour with brightness 0-100%
// #########################################################################
unsigned int brightness(unsigned int colour, int brightness)
{
  byte red   = colour >> 11;
  byte green = (colour & 0x7E0) >> 5;
  byte blue  = colour & 0x1F;

  blue =  (blue * brightness) / 100;
  green = (green * brightness) / 100;
  red =   (red * brightness) / 100;

  return (red << 11) + (green << 5) + blue;
}




void setup(){
Serial.begin(115200);
  tft.begin();

  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.fillCircle(120, 120, 120, brightness(TFT_WHITE, 50));

setupCardio();
setupVario();
}


void loop(){
  loopVario();
  loopCardio();
  int cardioOut = map(BPM, 0, 230, 0, 360);
  tft.fillCircle(120, 120, 120, brightness(TFT_WHITE, 50));
  roundedArc(120, 120, 120, 10, 0, cardioOut, TFT_RED);
  int varioOut = map(estimated_Vario/100, -10, 10, -90, 90);
  roundedArc(120, 120, 105, 10, 90, varioOut, TFT_CYAN);
  delay(200);

}
