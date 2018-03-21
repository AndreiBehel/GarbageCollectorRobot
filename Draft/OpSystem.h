#ifndef OPSYSTEM_H
#define OPSYSTEM_H
#include <Arduino.h>
#include <Servo.h>
class OpSystem {
private:
  byte servPin;
  
  long intervalBeforeClosing;
  unsigned long previousMillis;
  unsigned int openConter;
  
  boolean state;
  boolean prevState;
  Servo servo;

  void Op();
  void Cl();
public:
	OpSystem(byte servo);
	void Update();
  void Open();
  void Close();
  void init();
  
  boolean isOpened();
  unsigned int lastOpened();
  unsigned int getOpenCount();
};
#endif
