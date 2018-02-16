#include "OpSystem.h"
OpSystem::OpSystem(int servoPin, int buttonCh) {
	buttonCheck = buttonCh;
	servPin = servoPin;
  intervalBeforeClosing = 60000;
  prevState = false;
  state = false; 
}

void OpSystem::Update() {
  if(prevState != state) {
    if(state) {
      Op();
      previousMillis = millis();
    } else {
      Cl();
    }
    prevState = state;
  }
  unsigned long currentMillis = millis();
    if ( prevState && ( currentMillis - previousMillis ) >= intervalBeforeClosing ) {
      Cl();
      previousMillis = currentMillis;
    }
}

void OpSystem::init() {
  servo.attach(servPin);
}

void OpSystem::Open() {
  state = true;
}

void OpSystem::Close() {
  state = false;
}

void OpSystem::Op() {
    servo.write(180);
}

void OpSystem::Cl() {
  servo.write(0);
}

