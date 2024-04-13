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
 
#include "DataStructure.h"

constexpr uint8_t esp_mac1[] = {0x84, 0xCC, 0xA8, 0x61, 0x01, 0x4C};

unsigned count1, count2;

bool CompareMacAddress(const uint8_t * mac0, const uint8_t * mac1) {
  return (mac0[0] == mac1[0] &&
        mac0[1] == mac1[1] &&
        mac0[2] == mac1[2] &&
        mac0[3] == mac1[3] &&
        mac0[4] == mac1[4] &&
        mac0[5] == mac1[5]);
}

// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&packet_buffer, incomingData, PACKET_SIZE * sizeof(char)); //Maybe we can take the incoming data directly OPTIMISATION!
  
  Serial.print("\t");

  if(CompareMacAddress(mac, esp_mac1)){
    count1++;
    Serial.print(count1);
    Serial.print("\t1");
  }
  else{
    Serial.print(count2);
    Serial.print("\t2");
    count2++;
  }
  
  Serial.print("\tData received: ");
  Serial.print(len);

  ReadBuffer(0);

  Serial.print("\tValue 1: ");
  Serial.print(compression.d[0]);
  Serial.print("\tValue 2: ");
  Serial.println(compression.d[1]);
}
 
void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);
  
  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Register callback function
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
 
}