#ifndef IRSENSOR_H
#define IRSENSOR_H
#include <Arduino.h>
class IRSensor {
public:
	IRSensor(int pin, long interval);
	void Update();
	double getCurrentValue();
private:
	double getDistance();
	int irPin; 
	long intervalOfUpdate;
	// These maintain the current state
	double distValue;
	unsigned long previousMillis;
};
#endif