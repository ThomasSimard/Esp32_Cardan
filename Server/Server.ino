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

/*Pinout for status leds*/
constexpr unsigned COMMr = 7;  //Change pinout accordint to ESP
constexpr unsigned COMMg = 4;
constexpr unsigned COMMb = 6;

constexpr unsigned SDr = 7;  //Change pinout accordint to ESP
constexpr unsigned SDg = 4;
constexpr unsigned SDb = 6;

constexpr unsigned GPSr = 7;  //Change pinout accordint to ESP
constexpr unsigned GPSg = 4;
constexpr unsigned GPSb = 6;

/*initialisation carte SD*/
constexpr unsigned SD_ChipSelect = 10; 

constexpr unsigned Toggle = 5;


bool CompareMacAddress(const uint8_t * mac0, const uint8_t * mac1) {
  return (mac0[0] == mac1[0] &&
        mac0[1] == mac1[1] &&
        mac0[2] == mac1[2] &&
        mac0[3] == mac1[3] &&
        mac0[4] == mac1[4] &&
        mac0[5] == mac1[5]);
}

class RGB_LED{
  public:
  RGB_LED(int redPin, int greenPin, int bluePin) : redPin(redPin) , greenPin(greenPin), bluePin(bluePin){
  }

  void selectColour(int redValue, int greenValue, int blueValue){
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);
  }

  private:
  int redPin;
  int greenPin;
  int bluePin;
}


/*Define LEDs*/
RGB_LED comLED(COMMr, COMMg, COMMb);
RGB_LED sdLED(SDr, SDg, SDb);
RGB_LED GPSLED(GPSr, GPSg, GPSb);

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

      bool isRecording = digitalRead(Toggle);

      sdLED.selectColour(255, 255, 1)  //jaune, enregistrement en cours

      if(isRecording){
        if(!isOpen){
          // Open the file at the beginning of the program
        
          String filename = "data";
          do {
            filename = "data";
            filename += String(fileCount);
            filename += ".csv";

            fileCount++;
          }while(SD.exists(filename));

          myFile = SD.open(filename, FILE_WRITE);
          if (myFile) {
            D_println("File opened successfully");
            isOpen = true;

            delay(20);
          } else {
            D_println("Error opening file");
            digitalWrite(RedLed1, HIGH);
          }
      }
          MyFile.println(compression.d[0]);
          MyFile.println(compression.d[1]);

          }else{
            myFile.close();
            isOpen = false;
            sdLED.selectColour(1,255,1);
          }

          delay(20);
              break;
            }
  }
}
 
void setup() {
  // Set up Serial Monitor
  Serial.begin(115200);

  //carte SD
  pinMode(COMMr, OUTPUT);
  pinMode(COMMg, OUTPUT);
  pinMode(COMMb, OUTPUT);

  pinMode(SDr, OUTPUT);
  pinMode(SDg, OUTPUT);
  pinMode(SDb, OUTPUT);

  pinMode(GPSr, OUTPUT);
  pinMode(GPSg, OUTPUT);
  pinMode(GPSb, OUTPUT);

  pinMode(Toggle, INPUT);

  /* SD */
  while (!SD.begin(SD_ChipSelect)) {
    D_println("Card failed, or not present");
    sdLED.selectColour(255,1,1);
    delay(100);
  }
  D_println("Card initialized.");
  
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