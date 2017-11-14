#include <SoftwareSerial.h>
class RequestHandler {
  //const byte numChars = 32;
  char receivedChars[32];
  int index = 0;
  
  boolean isReceiving = false;
  boolean newMessage = false;
  
  char markerStart = '<';
  char markerEnd = '\r';

  char command[4];
  
  public:
  RequestHandler() {
    
  }
 void receiveMessage() {
  char rc;
  while(Serial.available() && !isReceiving) {
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
    if (rc = markerStart) {
      isReceiving = true;
    }
  }
 }
 void processMessage() {
  if(newMessage) {
    parseData();

    if(command[0] == 'w') {
      
    } else if(command[0] == 's') {
      
    } else if(command[0] == 'a') {
      
    } else if(command[0] == 'd') {
      
    } else if(command[0] == 's') {
      
    } else if(command[0] == 's') {
      
    } else if(command[0] == 's') {
      
    } else if(command[0] == 's') {
      
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

class Motor {
  int leftMotorDirPin;
  int rightMotorDirPin;
  int leftMotorPwmPin;
  int rightMotorPwmPin;
  
  long intervalOfUpdate;

  bool isMoving;
  unsigned long previousMillis;
  
  public:
  Motor(int leftDir, int rightDir, int leftPwm, int rightPwm) {
    leftMotorDirPin = leftDir;
    rightMotorDirPin = rightDir;
    leftMotorPwmPin = leftPwm;
    rightMotorPwmPin = rightPwm;

    pinMode(leftDir, OUTPUT);
    pinMode(rightDir, OUTPUT);
    pinMode(leftPwm, OUTPUT);
    pinMode(rightPwm, OUTPUT);

    isMoving = false;
  }
  
  void moveLeft(bool leftDir, int leftSpeed, int duration) {
    if(leftDir){
       digitalWrite(leftDir, HIGH);
    } else {
      digitalWrite(leftDir, LOW);
    }
    analogWrite(leftDir, leftSpeed);
  }

  void moveRight(bool rightDir, int rightSpeed, int duration) { 
    if(rightDir){
       digitalWrite(rightDir, HIGH);
    } else {
      digitalWrite(rightDir, LOW);
    }
    analogWrite(rightDir, rightSpeed);
  }
  
  void Update() {
    unsigned long currentMillis = millis();
    if(currentMillis - previousMillis >= intervalOfUpdate) {
      previousMillis = currentMillis;
    } else {
       
    }
  }
  void stopMoving() {
    digitalWrite(leftMotorPwmPin, LOW);
    digitalWrite(rightMotorPwmPin, LOW);
    digitalWrite(leftMotorDirPin, LOW);
    digitalWrite(rightMotorDirPin, LOW);
  }
};

class IRSensor {
  int irPin; 
  long intervalOfUpdate;

  // These maintain the current state
  double distValue;
  unsigned long previousMillis;
  
  public:
  IRSensor(int pin, long interval){
    irPin = pin;
    pinMode(irPin, INPUT);
      
    intervalOfUpdate = interval;
    previousMillis = 0;
  }
  
  void Update()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if(currentMillis - previousMillis >= intervalOfUpdate)
    {
      distValue = getDistance(); 
      previousMillis = currentMillis;  // Remember the time
    }
  }
  double getCurrentValue() {
    return distValue;
  }
  private:
  double getDistance(){
    double V = analogRead(irPin);
    return 2914. / (V + 5) - 1;
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

const int LEFT_DIR_PIN = 9;
const int LEFT_PWM_PIN = 9;
 
const int RIGHT_DIR_PIN = 9; 
const int RIGHT_PWM_PIN = 9;

const int SERVO_PIN = 9;

const int FRONT_IR_PIN = 9;
const int BACK_IR_PIN = 9;

const int ULTRASONIC_PIN = 9; 

const int BUTTON_PIN = 9;
const int CLOSE_DETECTOR_PIN = 9;

//Piezo Speaker
const int BUZER_PIN = 9; 

Motor mt(LEFT_DIR_PIN, RIGHT_DIR_PIN, LEFT_PWM_PIN, RIGHT_PWM_PIN);
RequestHandler rh;
IRSensor frIrSensor(FRONT_IR_PIN, 100);
IRSensor bcIrSensor(BACK_IR_PIN, 100);

void setup(){
  pinMode(SERVO_PIN, OUTPUT);

  pinMode(ULTRASONIC_PIN, INPUT);

  pinMode(BUTTON_PIN, INPUT);

  // Set buzzer - pin 9 as an output
  pinMode(BUZER_PIN, OUTPUT);
  // opens serial port, sets data rate to 9600 bps
  Serial.begin(9600);
}
void loop(){
  frIrSensor.Update();
  bcIrSensor.Update();
  rh.receiveMessage();
  rh.processMessage();
}
double getFrontDistance() {
  double V = analogRead(BACK_IR_PIN);
  return 2914. / (V + 5) - 1;
}
double getBackDistance() {
  double V = analogRead(BACK_IR_PIN);
  return 2914. / (V + 5) - 1;
}
//return fullness of the basket. changes from 1-5
int getFullness() {
  return 1;
}

bool openBasket() {
  
}

bool isBasketOpened() {
  if(digitalRead(CLOSE_DETECTOR_PIN) == HIGH) {
    return false;
  } else {
    return true;
  }
}

bool isMoving() {
  return false;
}

double getTemperature() {
  return 20;
}

void playSignal() {
  tone(BUZER_PIN, 1000); // Send 1KHz sound signal...
  delay(1000);        // ...for 1 sec
  noTone(BUZER_PIN);     // Stop sound...
  delay(1000);        // ...for 1sec
}

void move(int speed, int duration) {

  digitalWrite(LEFT_DIR_PIN, HIGH);
  digitalWrite(RIGHT_DIR_PIN, HIGH);
  //analogWrite(LEFT_PWM_PIN, );
  //analogWrite(RIGHT_PWM_PIN, );
}


