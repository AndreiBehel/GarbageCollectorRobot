#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include <Arduino.h>
#include "Motor.h"
#include "OpSystem.h"
#include "MessageSender.h"

class RequestHandler {
private:
	Motor* mt;
  OpSystem* opSystem;
  MessageSender* messageSender;
  
	char receivedChars[10];
	int index = 0;

	boolean isReceiving = false;
	boolean newMessage = false;

	char markerStart = '<';
	char markerEnd = '>';

	char command[3];
  int commandParam[3] = {0,0,0};
  
	void parseData();
 const char servo = 's';
 const char backIR = 'b';
 const char frontIR = 'f';
 const char move = 'm';
 const char moveForw = 'w';
 const char moveBack = 'b';
public:
	RequestHandler(Motor* m, OpSystem* o, MessageSender* ms);
  
	void receiveMessage();
	void processMessage();
  void sendMessage();
};
#endif
