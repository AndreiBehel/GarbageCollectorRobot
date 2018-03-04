#include "Motor.h"  
Motor::Motor(int leftDir, int rightDir, int leftPwm, int rightPwm) {
    leftMotorDirPin = leftDir;
    rightMotorDirPin = rightDir;
    leftMotorPwmPin = leftPwm;
    rightMotorPwmPin = rightPwm;

    pinMode(leftMotorDirPin, OUTPUT);
    pinMode(rightMotorDirPin, OUTPUT);
    pinMode(leftMotorPwmPin, OUTPUT);
    pinMode(rightMotorPwmPin, OUTPUT);
    
    stopMoving();
  }

  void Motor::moveLeft(bool leftDir, int leftSpeed, int duration) {
    if(leftDir){
       digitalWrite(leftMotorDirPin, HIGH);
    } else {
      digitalWrite(leftMotorDirPin, LOW);
    }
    analogWrite(leftMotorPwmPin, leftSpeed);
  }

  void Motor::moveRight(bool rightDir, int rightSpeed, int duration) { 
    if(rightDir){
       digitalWrite(rightMotorDirPin, HIGH);
    } else {
      digitalWrite(rightMotorDirPin, LOW);
    }
    analogWrite(rightMotorPwmPin, rightSpeed);
  }
  
  void Motor::moveFr(double duration) {
  	digitalWrite(leftMotorDirPin, HIGH);
  	digitalWrite(rightMotorDirPin, HIGH);
    digitalWrite(leftMotorPwmPin, LOW);
    digitalWrite(rightMotorPwmPin, LOW);

  	intervalOfUpdate = duration;
    previousMillis = millis();
    
  	isMoving = true;
  }
  
  void Motor::moveBc(double duration) {
  	digitalWrite(leftMotorDirPin, LOW);
  	digitalWrite(rightMotorDirPin, LOW);
    digitalWrite(leftMotorPwmPin, HIGH);
    digitalWrite(rightMotorPwmPin, HIGH);
    
  	intervalOfUpdate = duration;
    previousMillis = millis();
    
  	isMoving = true;    
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

    intervalOfUpdate = duration;
    previousMillis = millis();
    
    isMoving = true;   
  }

