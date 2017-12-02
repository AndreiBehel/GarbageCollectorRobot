#ifndef IRSENSOR_H
#define IRSENSOR_H
#include <Arduino.h>
class IRSensor {
private:
  byte irPin; 
  byte numOfMes = 5;
  byte compensation = 5;
  
  long intervalOfUpdate;
  unsigned long previousMillis;
  
  double distValue;
 
  double getDistance();
public:
	IRSensor(int pin, long interval);
 
	void Update();
	double getCurrentValue();
};
#endif
