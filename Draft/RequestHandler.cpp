#include "RequestHandler.h"
RequestHandler::RequestHandler(Motor* m, OpSystem* o, MessageSender* ms) {
	mt = m;
  opSystem = o;
  messageSender = ms;
}

void RequestHandler::receiveMessage() {
	char rc;
	while (Serial.available() && !newMessage) {
		rc = Serial.read();
		if ( isReceiving) {
			if (rc != markerEnd) {
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
	if (newMessage) {
		parseData();
		if (command[0] == 'w') {
			Serial.println("move forward");
			mt -> moveFr(commandParam[0]);
      
		} else if (command[0] == 's') {
			Serial.println("move backward");
			mt -> moveBc(commandParam[0]);
     
		} else if (command[0] == 'a') {
			mt -> moveLeft(true, 20, 2000);
     
		} else if (command[0] == 'd') {
			mt -> moveRight(true, 20, 2000);
      
		} else if (command[0] == 'm') {
              
    } else if (command[0] == frontIR) {
      messageSender -> add("front sensor\n");
			messageSender -> setIrSendInterval(commandParam[0]);
      
		} else if (command[0] == backIR) {
      messageSender -> add("back sensor\n");

		} else if (command[0] == servo) {
      Serial.print( "Open " );
      opSystem -> Close();
		} else {
      
		}
		newMessage = false;
	}
}

void RequestHandler::parseData() {
	char* index;
	// obtain command
	index = strtok(receivedChars,",");
	strcpy(command, index);
	//split 1 parameter and convert to integer
	index = strtok(NULL, ",");
	commandParam[0] = atoi(index);
	/*split 1 parameter and convert to double
	index = strtok(NULL, ","); 
	floatFromPC = atof(index);*/
}


