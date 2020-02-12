#define VARIO_PWR false     //Turn on vario code
#define VARIO_DEBUG false  //Turn on Vario serial output
#define CARDIO_DEBUG true //Turn on Cardio serial output
#define GPS_DEBUG false    //Turn on GPS serial output



#include "Variables.h"

#include "varioFile.h"
#include "cardioFile.h"
#include "gpsFile.h"
//#include "sdFile.h"


TaskHandle_t VarioCore;
TaskHandle_t CardioCore;
TaskHandle_t GPSCore;
//TaskHandle_t SDCore;

void setup(){
    xTaskCreatePinnedToCore(VarioCode,  "VarioCore",  1024, NULL, 2, NULL, 1); //void name, Task name, Stack size, parameter as input, priority, task handle, core
    xTaskCreatePinnedToCore(CardioCode, "CardioCore", 1024, NULL, 2, NULL, 1);
    xTaskCreatePinnedToCore(GPSCode,    "GPSCore",    2048, NULL, 2, NULL, 1);
    //xTaskCreatePinnedToCore(SDCode,     "SDCore",     4096, NULL, 2, NULL, 1);

    if(!SD.begin(4)){
        Serial.println("Card Mount Failed");
        return;
    }
    uint8_t cardType = SD.cardType();

    if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        return;
    }

    Serial.print("SD Card Type: ");
    if(cardType == CARD_MMC){
        Serial.println("MMC");
    } else if(cardType == CARD_SD){
        Serial.println("SDSC");
    } else if(cardType == CARD_SDHC){
        Serial.println("SDHC");
    } else {
        Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD.cardSize() / (1024 * 1024);
    Serial.printf("SD Card Size: %lluMB\n", cardSize);

    listDir(SD, "/", 0);
    createDir(SD, "/mydir");
    listDir(SD, "/", 0);
    removeDir(SD, "/mydir");
    listDir(SD, "/", 2);
    writeFile(SD, "/hello.txt", "Hello ");
    appendFile(SD, "/hello.txt", "World!\n");
    readFile(SD, "/hello.txt");
    deleteFile(SD, "/foo.txt");
    renameFile(SD, "/hello.txt", "/foo.txt");
    readFile(SD, "/foo.txt");
    testFileIO(SD, "/test.txt");
    Serial.printf("Total space: %lluMB\n", SD.totalBytes() / (1024 * 1024));
    Serial.printf("Used space: %lluMB\n", SD.usedBytes() / (1024 * 1024));
}






















void loop(){}
