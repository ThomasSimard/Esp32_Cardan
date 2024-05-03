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
    myFile = SD.open(path + "log.csv", FILE_WRITE);

    if (myFile) {
      //Success opening fine

      myFile.println(compression.d[0]);
      myFile.println(compression.d[1]);
    } else {
      //("Error opening file");
    }
  }

  void GetFileName() {
    do {
      path = "data";
      path += String(fileCount);
      //path += ".csv";

      fileCount++;
    }while(SD.exists(path));
  }

  void CreateDir(const String& path){
    if(SD.mkdir(path)){
      Serial.println("Dir created");
    } else {
      Serial.println("mkdir failed");
    }
  }

  void Initialize() {
    // Set microSD Card CS as OUTPUT and set HIGH
    pinMode(CS, OUTPUT);      
    digitalWrite(CS, HIGH); 
    
    // Initialize SPI bus for microSD Card
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);

    while (!SD.begin(CS)) {
      // No sd card
      Serial.println("PROBLEME SD");
      delay(100);
    }

    GetFileName();
    CreateDir(path);
  }
}

#endif