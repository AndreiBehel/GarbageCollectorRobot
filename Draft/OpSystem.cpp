#include "OpSystem.h"
OpSystem::OpSystem(int servoPin, int buttonOp, int buttonCh) {
	buttonOpen = buttonOp;
	buttonCheck = buttonCh;
	servPin = servoPin;

  block = false;
  intervalOfUpdate = 2000;
  intervalBeforeClosing = 60000;
}
void OpSystem::Update() {
  unsigned long currentMillis = millis();
    if( currentMillis - previousMillis >= intervalOfUpdate ) {
      if( digitalRead(buttonOpen) == HIGH ) {
        
      }
      block = false;
      previousMillis = currentMillis;
    }
}
void OpSystem::init() {
  servo.attach(servPin);
}
boolean OpSystem::Open() {
  if (!block) {
    servo.write(180);
    block = true;
  }
  Serial.println(block);
  return block;
}
boolean OpSystem::Close() {
  if (!block) {
    servo.write(0);
    block = true;
  }
  Serial.println(block);
  return block;
}


