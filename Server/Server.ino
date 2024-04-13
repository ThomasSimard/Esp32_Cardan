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

unsigned count;

// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&packet_buffer, incomingData, PACKET_SIZE * sizeof(char));
  
  count++;
  
  Serial.print(count);
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