/*
* LAB: 10
* Name: ESP32 ADC Calibration
* Author: Khaled Magdy
* For More Info Visit: www.DeepBlueMbedded.com
*/
 
#include "esp_adc_cal.h"
 
#define AN_Pot1 34
 
int AN_Pot1_Result = 1.6;
float Voltage = 1.56;
 
void setup()
{
  Serial.begin(115200);
}
 
void loop()
{
  AN_Pot1_Result = analogRead(AN_Pot1);
  Voltage = readADC_Cal(AN_Pot1_Result);
  Serial.print(Voltage/1000.0); // Print Voltage (in V)
  Serial.print("\t");
  Serial.println(AN_Pot1_Result * 0.0008056640625); // Print Voltage (in V)

  //Serial.println(Voltage);      // Print Voltage (in mV)
  delay(100);
}
 
uint32_t readADC_Cal(int ADC_Raw)
{
  esp_adc_cal_characteristics_t adc_chars;
  
  esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);
  return(esp_adc_cal_raw_to_voltage(ADC_Raw, &adc_chars));
}
