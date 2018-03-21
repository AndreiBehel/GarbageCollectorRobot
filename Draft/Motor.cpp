#include "Motor.h"  
Motor::Motor(byte leftDir, byte rightDir, byte leftPwm, byte rightPwm) {
    leftMotorDirPin = leftDir;
    rightMotorDirPin = rightDir;
    leftMotorPwmPin = leftPwm;
    rightMotorPwmPin = rightPwm;

    pinMode(leftMotorDirPin, OUTPUT);
    pinMode(rightMotorDirPin, OUTPUT);
    pinMode(leftMotorPwmPin, OUTPUT);
    pinMode(rightMotorPwmPin, OUTPUT);
    
    stopMoving();
    lastMoveMillis = millis();
  }

  void Motor::moveLeft(bool leftDir, int leftSpeed, unsigned int duration) {
    if(leftDir){
       digitalWrite(leftMotorDirPin, HIGH);
    } else {
      digitalWrite(leftMotorDirPin, LOW);
    }
    analogWrite(leftMotorPwmPin, leftSpeed);
  }

  void Motor::moveRight(bool rightDir, int rightSpeed, unsigned int duration) { 
    if(rightDir){
       digitalWrite(rightMotorDirPin, HIGH);
    } else {
      digitalWrite(rightMotorDirPin, LOW);
    }
    analogWrite(rightMotorPwmPin, rightSpeed);
  }
  
  void Motor::moveFr(unsigned int duration) {
  	digitalWrite(leftMotorDirPin, HIGH);
  	digitalWrite(rightMotorDirPin, HIGH);
    digitalWrite(leftMotorPwmPin, LOW);
    digitalWrite(rightMotorPwmPin, LOW);

    updateState(duration); 
  }
  
  void Motor::moveBc(unsigned int duration) {
  	digitalWrite(leftMotorDirPin, LOW);
  	digitalWrite(rightMotorDirPin, LOW);
    digitalWrite(leftMotorPwmPin, HIGH);
    digitalWrite(rightMotorPwmPin, HIGH);
    
    updateState(duration);
  }
  
  void Motor::Update() {
    unsigned long currentMillis = millis();
    if(isMoving && (currentMillis - previousMillis >= intervalOfUpdate)) {
      stopMoving();
      previousMillis = currentMillis;
    }
  }
  
  void Motor::stopMoving() {
    digitalWrite(leftMotorPwmPin, LOW);
    digitalWrite(rightMotorPwmPin, LOW);
    digitalWrite(leftMotorDirPin, LOW);
    digitalWrite(rightMotorDirPin, LOW);

	  isMoving = false;
    lastMoveMillis = intervalOfUpdate;
  }
  
  void Motor::move(bool leftDir, byte leftSpeed, bool rightDir, byte rightSpeed, unsigned int duration) {
    if(leftDir){
       digitalWrite(leftMotorDirPin, HIGH);
       leftSpeed = 255 - leftSpeed;
    } else {
      digitalWrite(leftMotorDirPin, LOW);
    }
    if(rightDir){
      digitalWrite(rightMotorDirPin, HIGH);
      rightSpeed = 255 - rightSpeed;
    } else {
      digitalWrite(rightMotorDirPin, LOW);
    }
    analogWrite(leftMotorPwmPin, leftSpeed);
    analogWrite(rightMotorPwmPin, rightSpeed);

    updateState(duration); 
  }

  void Motor::updateState(unsigned int duration) {
    intervalOfUpdate = duration;
    if (isMoving)
      lastMoveMillis = millis() - previousMillis;
    previousMillis = millis();
    
    isMoving = true;   
  }
  
boolean Motor::moving() {
  return isMoving;
}

unsigned int Motor::getLastMoveMillis() {
  return lastMoveMillis / 100;
}
