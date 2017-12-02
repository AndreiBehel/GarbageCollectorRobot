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
	  Servo servo;
	  byte buttonOpen;
	  byte buttonCheck;


    boolean block;
public:
	OpSystem(int servo, int buttonOp, int buttonCh);
	void Update();
  boolean Open();
  boolean Close();
  void init();
};
#endif
