#ifndef IRSENSOR_H
#define IRSENSOR_H
#include <Arduino.h>
class IRSensor {
public:
	IRSensor(int pin, long interval);
	void Update();
	double getCurrentValue();
private:
	int irPin; 
	double distValue;
  long intervalOfUpdate;
	unsigned long previousMillis;

  double getDistance();
};
#endif
