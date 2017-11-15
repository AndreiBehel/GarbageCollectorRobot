#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include <Arduino.h>
#include "Motor.h"
#include "IRSensor.h"

class RequestHandler {
private:
	Motor* mt;
	IRSensor* frIrSensor;
	IRSensor* bcIrSensor;

	//const byte numChars = 10;
	char receivedChars[10];
	int index = 0;

	boolean isReceiving = false;
	boolean newMessage = false;

	char markerStart = '<';
	char markerEnd = '>';

	char command[4];

	void RequestHandler::parseData();
public:
	RequestHandler(Motor* m, IRSensor* f, IRSensor* b);
	void receiveMessage();
	void processMessage();
};
#endif
