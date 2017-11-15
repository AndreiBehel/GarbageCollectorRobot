#ifndef MOTOR_H
  #define MOTOR_H
#include <Arduino.h>
class Motor {
private:
  int leftMotorDirPin;
  int rightMotorDirPin;
  int leftMotorPwmPin;
  int rightMotorPwmPin;
  
  long intervalOfUpdate;

  bool isMoving;
  unsigned long previousMillis;
  
  public:
  Motor(int leftDir, int rightDir, int leftPwm, int rightPwm);
  
  void moveLeft(bool leftDir, int leftSpeed, int duration);

  void moveRight(bool rightDir, int rightSpeed, int duration);
  void moveFr(double duration);
  void moveBc(double duration);
  void Update();
  void stopMoving();
};

#endif