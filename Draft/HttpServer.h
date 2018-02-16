#ifndef HTTPSERVER_H
#define HTTPSERVER_H
#include <Arduino.h>
#include <WiFlyHQ.h>
#include <SoftwareSerial.h>
#include "Motor.h"
#include "OpSystem.h"
#include "IRSensor.h"
#include "Battery.h"

class HttpServer {
private:
	Motor* mt;
	OpSystem* opSystem;
  IRSensor* frIrSensor;
  IRSensor* bcIrSensor;
  Battery* battery;
  
  WiFly* wifly;
  char buf[80];
  
	void sendIndex();
	void sendGreeting(char *name);
	void send404();
  void send200(char* str);

	char convBuff[10];
  int getTime(char* str);
  bool HttpServer::parseReqStr(char* str, byte* params);
  byte params[5];
  
public:
	void receive();
	HttpServer(Motor* m, OpSystem* o, IRSensor* f, IRSensor* b, Battery* bat, WiFly* wifly);
  getTime(char* str, byte pos);
};
#endif
