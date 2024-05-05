// Include Libraries
#include <esp_now.h>
#include <WiFi.h>

#include <DataStructure.h> //Put the Local Libraries DataStructure folder into your arduinos library folder
#include "RGB_LED.h"
#include "SD_CARD.h"

#include <TinyGPS++.h>

#define GPS_BAUDRATE 9600  // The default baudrate of NEO-6M is 9600

TinyGPSPlus gps;  // the TinyGPS++ object

#define RXD2 16
#define TXD2 17

#define ULONG_MAX (LONG_MAX * 2UL + 1UL)

/*initialisation carte SD*/
constexpr unsigned SD_ChipSelect = 5; 

constexpr unsigned Toggle = 22;

bool CompareMacAddress(const uint8_t * mac0, const uint8_t * mac1) {
  return (mac0[0] == mac1[0] &&
        mac0[1] == mac1[1] &&
        mac0[2] == mac1[2] &&
        mac0[3] == mac1[3] &&
        mac0[4] == mac1[4] &&
        mac0[5] == mac1[5]);
}


/*Define LEDs*/
//RGB_LED comLED(34, 35, 32);
//RGB_LED sdLED(33, 25, 26);
//RGB_LED gpsLED(27, 14, 12);

RGB_LED comLED(27, 25, 26);


class Capteur {
private:
  uint8_t mac[6];
public:
  Capteur(const uint8_t * p_mac){
    memcpy(&mac, p_mac, 6 * sizeof(uint8_t));
  }

  bool CheckMac(const uint8_t * p_mac) const { return CompareMacAddress(p_mac, mac); };
};

Capteur ESPs[] = { 
  Capteur(client_address)
};

bool lastRecording = true;

bool updateToggle(){
 bool isToggled = !digitalRead(Toggle);

 if(isToggled){
  SD_CARD::LED.selectColor(0, 50, 0);
 }else{
  SD_CARD::LED.selectColor(0, 0, 100);
 }
 
 return isToggled;
}

unsigned fileTimer = 0;
unsigned fileLineMax = 3;

// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(Data));

  Serial.println(data.flags);

  if(updateToggle()){
    SD_CARD::LogSDCard(data.flags);

    lastRecording = true;
  }else if(lastRecording){
    SD_CARD::GetFileName();
    SD_CARD::myFile.close();
    SD_CARD::myFile = SD.open(SD_CARD::path + "/log.csv", FILE_WRITE);

    lastRecording = false;
  }
}
 
void setup() {
  // Set up Serial Monitor
  Serial.begin(9600);
  Serial2.begin(GPS_BAUDRATE, SERIAL_8N1,RXD2,TXD2);

  pinMode(Toggle, INPUT);
  SD_CARD::Initialize();
  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    ESP.restart();
  }

  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);

  updateToggle();

  //comLED.selectColour(0, 0, 50);
}

void loop() {
  if (Serial2.available() > 0) {
    if (gps.encode(Serial2.read())) {
      if (SD_CARD::myFile) {
        if (gps.location.isValid()) {
          //Success opening fine
          SD_CARD::myFile.print("GPS,Location,VALID,Latitude,");
          SD_CARD::myFile.print(gps.location.lat());
          SD_CARD::myFile.print(",Longitude,");
          SD_CARD::myFile.print(gps.location.lng());
          SD_CARD::myFile.print(",Altitude,");

          if (gps.altitude.isValid())
            SD_CARD::myFile.println(gps.altitude.meters());
          else
            SD_CARD::myFile.println("INVALID");
        } else {
          SD_CARD::myFile.println("GPS,Location,INVALID");
        }

        if (gps.speed.isValid()) {
          SD_CARD::myFile.print("GPS,Speed,VALID,");
          SD_CARD::myFile.println(gps.speed.kmph());
        } else {
          SD_CARD::myFile.println("GPS,Speed,INVALID");
        }

        if (gps.date.isValid() && gps.time.isValid()) {
          SD_CARD::myFile.print("GPS,Date,VALID,");
          SD_CARD::myFile.print(gps.date.year());
          SD_CARD::myFile.print("-");
          SD_CARD::myFile.print(gps.date.month());
          SD_CARD::myFile.print("-");
          SD_CARD::myFile.print(gps.date.day());
          SD_CARD::myFile.print(" ");
          SD_CARD::myFile.print(gps.time.hour());
          SD_CARD::myFile.print(":");
          SD_CARD::myFile.print(gps.time.minute());
          SD_CARD::myFile.print(":");
          SD_CARD::myFile.print(gps.time.second());
        } else {
          SD_CARD::myFile.println("GPS,Date,INVALID");
        }

        SD_CARD::myFile.print("Time Refference,");
        SD_CARD::myFile.println(millis());

        SD_CARD::myFile.flush();
      }
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10){
    Serial.println(F("No GPS data received: check wiring"));
  }

  delay(10);
}
