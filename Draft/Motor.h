#ifndef MOTOR_H
  #define MOTOR_H
#include <Arduino.h>
class Motor {
private:
  long intervalOfUpdate;
  unsigned long previousMillis;
  
  byte leftMotorDirPin;
  byte rightMotorDirPin;
  byte leftMotorPwmPin;
  byte rightMotorPwmPin;
  
  bool isMoving;  
public:
  Motor(byte leftDir, byte rightDir, byte leftPwm, byte rightPwm);
  
  void moveLeft(bool leftDir, int leftSpeed, unsigned int duration);
  void moveRight(bool rightDir, int rightSpeed, unsigned int duration);
  void moveFr(unsigned int duration);
  void moveBc(unsigned int duration);
  void move(bool leftDir, byte leftSpeed, bool rightDir, byte rightSpeed, unsigned int duration);
  void Update();
  void stopMoving();

  boolean moving() {
    return isMoving;
  }
};

#endif
