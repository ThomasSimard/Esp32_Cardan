/*
  ESP-NOW Demo - Receive
  esp-now-demo-rcv.ino
  Reads data from Initiator
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/
 
// Include Libraries
#include <esp_now.h>
#include <WiFi.h>

#include <DataStructure.h> //Put the Local Libraries DataStructure folder into your arduinos library folder

#define ULONG_MAX (LONG_MAX * 2UL + 1UL)

bool CompareMacAddress(const uint8_t * mac0, const uint8_t * mac1) {
  return (mac0[0] == mac1[0] &&
        mac0[1] == mac1[1] &&
        mac0[2] == mac1[2] &&
        mac0[3] == mac1[3] &&
        mac0[4] == mac1[4] &&
        mac0[5] == mac1[5]);
}

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
  Capteur(broadcaster_address)
};

// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&data, incomingData, sizeof(Data));

  for(const auto& ESP : ESPs){
    if(ESP.CheckMac(mac)){
      Serial.print(data.flags);
      Serial.print("\t");
      Serial.print(millis());
      Serial.print("\t");

      ReadBuffer(0);

      Serial.print("Value 1: ");
      Serial.print(compression.d[0]);
      Serial.print("\tValue 2: ");
      Serial.println(compression.d[1]);
      break;
    }
  }
}
 
void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);
  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    ESP.restart();
  }
  
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
 
}