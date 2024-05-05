#ifndef SD_CARD_h
#define SD_CARD_h
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

namespace SD_CARD {
  constexpr unsigned CS = 5;
  constexpr unsigned SPI_MOSI = 23;
  constexpr unsigned SPI_MISO = 19;
  constexpr unsigned SPI_SCK = 18;

  File myFile;  // Création du fichier pour la carte SD
  unsigned fileCount = 0;
  String path = "/data";

  RGB_LED LED(14, 12, 13);

  void LogSDCard(const unsigned& flags){
    if (myFile) {
      //Success opening fine
      myFile.print("Esp,");
      myFile.print(flags);
      myFile.print(",Temps,");
      myFile.println(millis());

      for(unsigned i = 0; i < 83; i++){
        ReadBuffer(i);
        
        myFile.print(compression.d[0]);
        myFile.print(",");
        myFile.print(compression.d[1]);
        myFile.print(",");
      }
      myFile.println("");

      myFile.flush();
    } else {
      Serial.print("Error opening file");
    }
  }

  void GetFileName() {
    do {
      path = "/data";
      path += String(fileCount);

      fileCount++;
    }while(SD.exists(path));
  }

  void CreateDir(const String& path){
    if(SD.mkdir(path.c_str())){
      Serial.println("Dir created");
    } else {
      Serial.println("mkdir failed");
    }
  }

  void Initialize() {
    // Initialize SPI bus for microSD Card
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, CS);

    while (!SD.begin(CS)) {
      // No sd card
      Serial.println("PROBLEME SD");
      LED.selectColor(200, 50, 0);
      delay(100);
    }

    GetFileName();
    CreateDir(path);

    myFile = SD.open(SD_CARD::path + "/log.csv", FILE_WRITE);
  }
}

#endif