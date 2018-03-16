#include "OpSystem.h"
OpSystem::OpSystem(byte servoPin, byte buttonCh) {
	buttonCheck = buttonCh;
	servPin = servoPin;
 
  intervalBeforeClosing = 60000;
  prevState = false;
  state = false; 

  openConter = 0;
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
  }
}

void OpSystem::init() {
  servo.attach(servPin);
  servo.write(0);
  delay(900);
  servo.detach();
}

void OpSystem::Open() {
  state = true;
}

void OpSystem::Close() {
  state = false;
}

void OpSystem::Op() {
  servo.attach(servPin);
  servo.write(170);
  delay(900);
  servo.detach();
  openConter++;
}

void OpSystem::Cl() {
  servo.attach(servPin);
  servo.write(0);
  delay(900);
  servo.detach();
}

boolean OpSystem::isOpened() {
  return state;
}

unsigned int OpSystem::lastOpened() {
  return (millis() - previousMillis) / 60000;
}

unsigned int OpSystem::getOpenCount() {
  return openConter;
}


