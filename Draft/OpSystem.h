#ifndef OPSYSTEM_H
#define OPSYSTEM_H
#include <Arduino.h>
#include <Servo.h>
class OpSystem {
private:
  byte servPin;
  
  long intervalOfUpdate;
  long intervalBeforeClosing;
  unsigned long previousMillis;
  
  boolean state;
  boolean prevState;
  Servo servo;
  byte buttonCheck;

public:
	OpSystem(int servo, int buttonCh);
	void Update();
  void Open();
  void Close();
  void init();
};
#endif
