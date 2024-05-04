// Include Libraries
#include <esp_now.h>
#include <WiFi.h>

#include <DataStructure.h> //Put the Local Libraries DataStructure folder into your arduinos library folder
#include "RGB_LED.h"
#include "SD_CARD.h"

#define ULONG_MAX (LONG_MAX * 2UL + 1UL)

/*initialisation carte SD*/
constexpr unsigned SD_ChipSelect = 5; 

bool isOpen = false;
int fileCount = 0;
File myFile;

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
 bool isToggled = digitalRead(Toggle);

 if(isToggled){
  SD_CARD::LED.selectColor(0, 50, 0);
 }else{
  SD_CARD::LED.selectColor(0, 0, 0);
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
    if(fileTimer == 0){
      SD_CARD::myFile = SD.open(SD_CARD::path + "/log.csv", FILE_WRITE);
    }

    fileTimer++;
    SD_CARD::LogSDCard(data.flags);

    if(fileTimer >= fileLineMax){
      fileTimer = 1;
    }

    lastRecording = true;
  }else if(lastRecording){
    SD_CARD::GetFileName();

    lastRecording = false;
  }
}
 
void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);
  Serial.print("init");

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
}
