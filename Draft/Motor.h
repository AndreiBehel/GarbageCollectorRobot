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
  Motor(int leftDir, int rightDir, int leftPwm, int rightPwm);
  
  void moveLeft(bool leftDir, int leftSpeed, int duration);
  void moveRight(bool rightDir, int rightSpeed, int duration);
  void moveFr(double duration);
  void moveBc(double duration);
  void update();
  void stopMoving();
};

#endif
