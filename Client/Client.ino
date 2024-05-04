// Include Libraries
#include <esp_now.h>
#include <WiFi.h>
 
#include <DataStructure.h>
 
// Peer info
esp_now_peer_info_t peerInfo;

// Pins
constexpr unsigned short AnalogIn = 34;

// Callback function called when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {}
 
void setup() {
  // Save power
  setCpuFrequencyMhz(80);

  // Set ESP32 as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
 
  // Initilize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    ESP.restart();
  }
 
  // Register the send callback
  esp_now_register_send_cb(OnDataSent);
  
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

  data.flags = 2;

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(server_address, (uint8_t *)&data, sizeof(Data));

/*   
  if (result == ESP_OK) {
    Serial.println("Sending confirmed");
  }
  else {
    Serial.println("Sending error");
  }
*/
}