#include <SoftwareSerial.h>
#include "IRSensor.h"
#include "Motor.h"
#include "RequestHandler.h"
#include "OpSystem.h"
#include "MessageSender.h"

#include <MsTimer2.h>

#include "WiFlyHQ.h"
#include <SoftwareSerial.h>
SoftwareSerial wifiSerial(8,9);

WiFly wifly;

const char mySSID[] = "myssid";
const char myPassword[] = "my-wpa-password";

const int LEFT_DIR_PIN = 3;
const int LEFT_PWM_PIN = 4;
 
const int RIGHT_DIR_PIN = 5; 
const int RIGHT_PWM_PIN = 6;

const int FRONT_IR_PIN = A0;
const int BACK_IR_PIN = A1;

const int SERVO_PIN = 9;

const int ULTRASONIC_PIN = 9; 

const int BUTTON_OP_PIN = 9;
const int CLOSE_DETECTOR_PIN = 20;

//Piezo Speaker
const int BUZER_PIN = 9; 
//*******************************************

Motor mt(LEFT_DIR_PIN, RIGHT_DIR_PIN, LEFT_PWM_PIN, RIGHT_PWM_PIN);
IRSensor frIrSensor(FRONT_IR_PIN, 100);
IRSensor bcIrSensor(BACK_IR_PIN, 100);
OpSystem opSystem(SERVO_PIN, CLOSE_DETECTOR_PIN);
MessageSender ms(&frIrSensor, &bcIrSensor);
RequestHandler rh(&mt, &opSystem, &ms);


void setup() {
  opSystem.init();
  Serial.begin(9600);
  MsTimer2::set(500, interrupt);
  MsTimer2::start();
}

void loop() {
  
  rh.receiveMessage();
  rh.processMessage();

  ms.Update();
}

void interrupt(int timer) {
  frIrSensor.Update();
  bcIrSensor.Update();

  mt.Update();
  opSystem.Update();
}

