#include <SoftwareSerial.h>
#include "IRSensor.h"
#include "Motor.h"
#include "RequestHandler.h"

const int LEFT_DIR_PIN = 3;
const int LEFT_PWM_PIN = 4;
 
const int RIGHT_DIR_PIN = 5; 
const int RIGHT_PWM_PIN = 6;

const int SERVO_PIN = 9;

const int FRONT_IR_PIN = A0;
const int BACK_IR_PIN = A1;

const int ULTRASONIC_PIN = 9; 

const int BUTTON_PIN = 9;
const int CLOSE_DETECTOR_PIN = 9;

//Piezo Speaker
const int BUZER_PIN = 9; 
//*******************************************

Motor mt(LEFT_DIR_PIN, RIGHT_DIR_PIN, LEFT_PWM_PIN, RIGHT_PWM_PIN);
IRSensor frIrSensor(FRONT_IR_PIN, 100);
IRSensor bcIrSensor(BACK_IR_PIN, 100);
RequestHandler rh(&mt, &frIrSensor, &bcIrSensor);

void setup(){
  // opens serial port, sets data rate to 9600 bps
  Serial.begin(9600);
}

void loop(){
  frIrSensor.Update();
  bcIrSensor.Update();
  mt.Update();
  rh.receiveMessage();
  rh.processMessage(); 
}

bool isBasketOpened() {
  if(digitalRead(CLOSE_DETECTOR_PIN) == HIGH) {
    return false;
  } else {
    return true;
  }
}

void playSignal() {
  tone(BUZER_PIN, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(BUZER_PIN);     // Stop sound...
  delay(1000);        // ...for 1sec
}


