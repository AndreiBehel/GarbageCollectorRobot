
const int LEFT_DIR_PIN = 9; 
const int LEFT_PWM_PIN = 9;
 
const int RIGHT_DIR_PIN = 9; 
const int RIGHT_PWM_PIN = 9;

const int SERVO_PIN = 9; 

const int FRONT_IR_PIN = 9; 
const int BACK_IR_PIN = 9; 

const int ULTRASONIC_PIN = 9; 

const int BUTTON_PIN = 9;

//Piezo Speaker connected to arduino pin 9
const int BUZER_PIN = 9; 

void setup(){
  // Set buzzer - pin 9 as an output
  pinMode(BUZER_PIN, OUTPUT);
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
  return true;
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
   
}


