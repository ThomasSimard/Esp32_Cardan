#ifndef RGB_LED_h
#define RGB_LED_h
#include <Arduino.h>

class RGB_LED{
public:
  RGB_LED(const unsigned& redPin, const unsigned& greenPin, const unsigned& bluePin) : redPin(redPin) , greenPin(greenPin), bluePin(bluePin){
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    pinMode(bluePin, OUTPUT);
  }

  void selectColor(const unsigned short& redValue, const unsigned short& greenValue, const unsigned short& blueValue){
    analogWrite(redPin, redValue);
    analogWrite(greenPin, greenValue);
    analogWrite(bluePin, blueValue);
  }

private:
  int redPin;
  int greenPin;
  int bluePin;
};

#endif