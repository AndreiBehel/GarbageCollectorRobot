#include "IRSensor.h"
IRSensor::IRSensor(int pin, long interval) {
	irPin = pin;
	pinMode(irPin, INPUT);

	intervalOfUpdate = interval;
	previousMillis = 0;
}

void IRSensor::Update()
{
	// check to see if it's time to change the state of the LED
	unsigned long currentMillis = millis();

	if(currentMillis - previousMillis >= intervalOfUpdate)
	{
		distValue = getDistance(); 
		previousMillis = currentMillis;  // Remember the time
	}
}
double IRSensor::getCurrentValue() {
	return distValue;
}

double IRSensor::getDistance() {
	double V = analogRead(irPin);
	return 2914. / (V + 5) - 1;
}