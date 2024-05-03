// Include Libraries
#include <esp_now.h>
#include <WiFi.h>

#include <DataStructure.h> //Put the Local Libraries DataStructure folder into your arduinos library folder
#include "RGB_LED.h"
#include "SD_CARD.h"

#define ULONG_MAX (LONG_MAX * 2UL + 1UL)

/*initialisation carte SD*/
constexpr unsigned SD_ChipSelect = 5; 

//Esti d'ordi d'épais
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

RGB_LED sdLED(14, 12, 13);
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

// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(Data));

  //for(const auto& ESP : ESPs){
    //if(ESP.CheckMac(mac)){
      Serial.print(data.flags);
      Serial.print("\t");
      Serial.print(millis());
      Serial.print("\t");

      ReadBuffer(0);

      Serial.print("Value 1: ");
      Serial.print(compression.d[0]);
      Serial.print("\tValue 2: ");
      Serial.println(compression.d[1]);

      bool isRecording = digitalRead(Toggle);

      //sdLED.selectColour(255, 255, 1);  //jaune, enregistrement en cours

      if(isRecording){
        SD_CARD::LogSDCard();
      }
    //}
  //}
}
 
void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);
  Serial.print("init");

  pinMode(Toggle, INPUT);
  //SD_CARD::Initialize();
  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    ESP.restart();
  }

  File myFile;  // Création du fichier pour la carte SD
  bool isOpen = false;
  unsigned fileCount = 0;

  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);

  comLED.selectColour(0, 0, 50);
  sdLED.selectColour(50, 0, 0);
}

void loop() {
}
