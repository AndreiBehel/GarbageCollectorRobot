#ifndef MESSAGESENDER_H
  #define MESSAGESENDER_H
#include <Arduino.h>
#include "IRSensor.h"

class MessageSender {
private:
  long intervalOfUpdate;
  unsigned long previousMillis;

  unsigned int irSendInterval;
  unsigned int fulnessSendInterval;
  unsigned int tempSendInterval;
  unsigned int batterySendInterval;
  
  unsigned long irPrevMillis;
  unsigned long fullnessPrevMillis;
  unsigned long tempPrevMillis;
  
  IRSensor* frIrSensor;
  IRSensor* bcIrSensor;
  
  String message;
public:
  MessageSender(IRSensor* f, IRSensor* b);
  void add(String message);
  void send();
  void Update();
  
  void addIRData();
  void addFullnessData();
  void addTempData();
  void addBatteryData();

  void setIrSendInterval(unsigned int v);
  void setFullnessSendInterval(unsigned int v);
  void setTempSendInterval(unsigned int v);
  void setBatterySendInterval(unsigned int v);
};
#endif
