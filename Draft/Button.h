#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>
class Button {
private:
  int irPin; 
  boolean isOpened;
  long intervalOfUpdate;
  unsigned long previousMillis;
public:
  Button(int pin, long interval);
  void Update();
  double getCurrentState();
};
#endif
