#include "RequestHandler.h"
RequestHandler::RequestHandler(Motor* m, IRSensor* f, IRSensor* b) {
	mt = m;
	frIrSensor = f;
	bcIrSensor = b;
}
void RequestHandler::receiveMessage() {
	char rc;
	while(Serial.available() && !newMessage) {
		rc = Serial.read();
		if(isReceiving) {
			if(rc != markerEnd) {
				receivedChars[index++] = rc;
			} else {
				receivedChars[index] = '\0';
				index = 0;
				isReceiving = false;
				newMessage = true;
			}
		}
		else if (rc == markerStart) {
			isReceiving = true;
		}  
	}
}
void RequestHandler::processMessage() {
	if(newMessage) {
		parseData();
		if(command[0] == 'w') {
			Serial.println("command w");
			//mt -> moveLeft(true, 20, 2000);
			mt -> moveFr(2000);
		} else if(command[0] == 's') {
			Serial.println("command s");
			mt -> moveBc(2000);
			//mt -> moveRight(false, 20, 2000);
		} else if(command[0] == 'a') {
			mt -> moveLeft(true, 20, 2000);
		} else if(command[0] == 'd') {
			mt -> moveRight(true, 20, 2000);
		} else if(command[0] == '1') {
			Serial.println("command pr fr sens");
			Serial.println(frIrSensor -> getCurrentValue());
		} else if(command[0] == '2') {
			Serial.println("command pr bc sens");
			Serial.println(bcIrSensor -> getCurrentValue());
		} else if(command[0] == '3') {

		} else if(command[0] == '4') {

		} else {

		}
		newMessage = false;
	}
}
void RequestHandler::parseData() {
	char * index;
	// obtain command
	index = strtok(receivedChars,",");
	strcpy(command, index);
	/*//split 1 parameter and convert to integer
	index = strtok(NULL, ",");
	integerFromPC = atoi(index);
	//split 1 parameter and convert to double
	index = strtok(NULL, ","); 
	floatFromPC = atof(index);*/
}
