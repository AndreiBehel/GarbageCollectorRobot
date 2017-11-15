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
    
    digitalWrite(leftMotorPwmPin, LOW);
    digitalWrite(rightMotorPwmPin, LOW);
    digitalWrite(leftMotorDirPin, LOW);
    digitalWrite(rightMotorDirPin, LOW);
    
    isMoving = false;
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
  	analogWrite(leftMotorPwmPin, 50);
  	analogWrite(rightMotorPwmPin, 50);
  	intervalOfUpdate = duration;
    previousMillis = millis();
    
  	isMoving = true;
  }
  void Motor::moveBc(double duration) {
  	digitalWrite(leftMotorDirPin, LOW);
  	digitalWrite(rightMotorDirPin, LOW);
  	analogWrite(leftMotorPwmPin, 120);
  	analogWrite(rightMotorPwmPin, 120);
  	intervalOfUpdate = duration;
  
  	isMoving = true;
    previousMillis = millis();
  }
  
  void Motor::Update() {
    unsigned long currentMillis = millis();
    if(isMoving && (currentMillis - previousMillis >= intervalOfUpdate)) {
      stopMoving();
      previousMillis = currentMillis;
    } else {
       
    }
  }
  void Motor::stopMoving() {
    digitalWrite(leftMotorPwmPin, LOW);
    digitalWrite(rightMotorPwmPin, LOW);
    digitalWrite(leftMotorDirPin, LOW);
    digitalWrite(rightMotorDirPin, LOW);

	isMoving = false;
  }
