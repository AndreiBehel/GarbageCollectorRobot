#include <SoftwareSerial.h>
#include "IRSensor.h"
#include "Motor.h"

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

class RequestHandler {
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
  
  public:
  RequestHandler(Motor* m, IRSensor* f, IRSensor* b) {
    mt = m;
    frIrSensor = f;
    bcIrSensor = b;
  }
 void receiveMessage() {
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
 void processMessage() {
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
 void parseData() {
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
};

class Controller {
  //Motor mt;
  //IRSensor frIrSensor;
  //IRSensor bcIrSensor;
  public:
  Controller() {
    
  }
};
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


