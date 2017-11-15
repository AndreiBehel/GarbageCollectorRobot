#include "Motor.h"  
Motor::Motor(int leftDir, int rightDir, int leftPwm, int rightPwm) {
    leftMotorDirPin = leftDir;
    rightMotorDirPin = rightDir;
    leftMotorPwmPin = leftPwm;
    rightMotorPwmPin = rightPwm;

    pinMode(leftDir, OUTPUT);
    pinMode(rightDir, OUTPUT);
    pinMode(leftPwm, OUTPUT);
    pinMode(rightPwm, OUTPUT);

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
	analogWrite(leftMotorPwmPin, 60);
	analogWrite(rightMotorPwmPin, 60);
	intervalOfUpdate = duration;

	isMoving = true;
  }
  void Motor::moveBc(double duration) {
	digitalWrite(leftMotorDirPin, LOW);
	digitalWrite(rightMotorDirPin, LOW);
	analogWrite(leftMotorPwmPin, 60);
	analogWrite(rightMotorPwmPin, 60);
	intervalOfUpdate = duration;

	isMoving = true;
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
