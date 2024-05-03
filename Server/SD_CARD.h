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
  String path = "data";

  void LogSDCard(){
    myFile = SD.open("BAJA/0/log.csv", FILE_WRITE);

    if (myFile) {
      //Success opening fine

      myFile.println(compression.d[0]);
      myFile.println(compression.d[1]);

      myFile.close();
    } else {
      Serial.print("Error opening file");
    }
  }

  void GetFileName() {
    do {
      path = "data";
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
    //SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI, CS);

    SPIClass spi = SPIClass(VSPI);
    spi.begin(SPI_SCK, SPI_MISO, SPI_MOSI, CS);

    while (!SD.begin(CS,spi,80000000)) {
      // No sd card
      Serial.println("PROBLEME SD");
      delay(100);
    }

    GetFileName();
    CreateDir(path);
  }
}

#endif