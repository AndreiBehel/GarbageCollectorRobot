#include "OpSystem.h"
OpSystem::OpSystem(int servoPin, int buttonCh) {
	buttonCheck = buttonCh;
	servPin = servoPin;
  intervalOfUpdate = 2000;
  intervalBeforeClosing = 60000;
  prevState = false;
  state = false; 
}

void OpSystem::Update() {
  if(prevState != state) {
    if(state) {
      Open();
      previousMillis = millis();
    } else {
      Close();
    }
    prevState = state;
  }
  unsigned long currentMillis = millis();
    if ( prevState && ( currentMillis - previousMillis ) >= intervalBeforeClosing ) {
      Close();
      previousMillis = currentMillis;
    }
}

void OpSystem::init() {
  servo.attach(servPin);
}

void OpSystem::Open() {
    servo.write(180);
}

void OpSystem::Close() {
  servo.write(0);
}


