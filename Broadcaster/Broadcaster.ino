/*
  ESP-NOW Demo - Transmit
  esp-now-demo-xmit.ino
  Sends data to Responder
  
  DroneBot Workshop 2022
  https://dronebotworkshop.com
*/
 
// Include Libraries
#include <esp_now.h>
#include <WiFi.h>
 
#include <DataStructure.h> //Put the Local Libraries DataStructure folder into your arduinos library folder

// Peer info
esp_now_peer_info_t peerInfo;

// Pins
constexpr unsigned short AnalogIn = 36;

// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {}

// Callback function executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&broadcast_data, incomingData, sizeof(Data));

  broadcast_data.flags = Status::Broadcasted;

  esp_err_t result = esp_now_send(server_address, (uint8_t *)&broadcast_data, sizeof(Data));
}
 
void setup() {
  // Save power
  setCpuFrequencyMhz(80);

  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    ESP.restart();
  }
 
  // Register callback function
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);

  // Register peer
  memcpy(peerInfo.peer_addr, server_address, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    return;
  }
}
 
void loop() {
  // Get readings
  for(unsigned short i = 0; i < (PACKET_SIZE / 3); i++){
    compression.d[0] = analogRead(AnalogIn);
    compression.d[1] = analogRead(AnalogIn);

    WriteBuffer(i);
    delayMicroseconds(250); // Save power
  }

  data.flags = Status::Default;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(server_address, (uint8_t *)&data, sizeof(Data));
   
  /*if (result == ESP_OK) {
    Serial.println("Sending confirmed");
  }
  else {
    Serial.println("Sending error");
  }*/
}