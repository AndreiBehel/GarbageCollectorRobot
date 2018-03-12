#include "IRSensor.h"
IRSensor::IRSensor(byte pin, long interval) {
	irPin = pin;
	pinMode(irPin, INPUT);

	intervalOfUpdate = interval;
	previousMillis = 0;
}

void IRSensor::Update()
{
	// check to see if it's time to measure distance
	unsigned long currentMillis = millis();

	if(currentMillis - previousMillis >= intervalOfUpdate)
	{
		distValue = getDistance(); 
		previousMillis = currentMillis;  // Remember the time
	}
}

int IRSensor::getCurrentValue() {
	return distValue;
}

double IRSensor::getDistance() {
  //use medial filter
  int arr[numOfMes];
  for (byte i = 0; i < numOfMes; i++) {
    arr[i] = 6787 / analogRead(irPin);
  }	
  
  qsort(arr, numOfMes, sizeof(int), compare);
  
  return arr[2];
}

int IRSensor::compare( const void* a, const void* b)
{
  int int_a = *((int*)a);
  int int_b = *((int*)b);
  
  if (int_a == int_b)
    return 0;
  else if (int_a < int_b) 
    return -1;
  else 
    return 1;
}
