#include <SoftwareSerial.h>
#include <WiFlyHQ.h>
#include "IRSensor.h"
#include "Motor.h"
#include "RequestHandler.h"
#include "OpSystem.h"
#include "MessageSender.h"
#include "Battery.h"
#include "HttpServer.h"

#include <MsTimer2.h>

SoftwareSerial wifiSerial(2,3);
WiFly wifly;
char buf[80];

/* Change these to match your WiFi network */
const char mySSID[] = "MEIZU";
const char myPassword[] = "641_7540";

/*Motor connection*/
const int LEFT_DIR_PIN = 4;
const int LEFT_PWM_PIN = 5;
 
const int RIGHT_DIR_PIN = 6; 
const int RIGHT_PWM_PIN = 7;

const int FRONT_IR_PIN = A0;
const int BACK_IR_PIN = A1;

/*Servo pin connection*/
const int SERVO_PIN = 11;

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
Battery battery(3400, 4600, 15, 3);
MessageSender ms(&frIrSensor, &bcIrSensor, &battery);
//RequestHandler rh(&mt, &opSystem, &ms);
HttpServer httpserver(&mt, &opSystem, &frIrSensor, &bcIrSensor, &wifly);

void setup() {
  setupWiFI();
  
  opSystem.init();
  Serial.begin(9600);
  MsTimer2::set(500, interrupt);
  MsTimer2::start();
}

void loop() {
  httpserver.receive();

  ms.Update();
}

void interrupt(int timer) {
  frIrSensor.Update();
  bcIrSensor.Update();

  mt.Update();
  opSystem.Update();
}

void setupWiFI() 
{
  Serial.begin(115200);
  Serial.println(F("Starting"));
  Serial.print(F("Free memory: "));
  Serial.println(wifly.getFreeMemory(),DEC);

  wifiSerial.begin(9600);
  if (!wifly.begin(&wifiSerial, &Serial)) {
    Serial.println(F("Failed to start wifly"));
    wifly.terminal();
  }

  connection();
  Serial.println(F("Ready"));
}

void connection()
{
  /* Join wifi network if not already associated */
  if (!wifly.isAssociated()) {
    /* Setup the WiFly to connect to a wifi network */
    Serial.println(F("Joining network"));
    wifly.setSSID(mySSID);
    wifly.setPassphrase(myPassword);
    wifly.enableDHCP();
    wifly.save();

    if (wifly.join()) {
      Serial.println(F("Joined wifi network"));
    } else {
      Serial.println(F("Failed to join wifi network"));
      wifly.terminal();
    }
  } else {
      Serial.println(F("Already joined network"));
  }
    
  wifly.setBroadcastInterval(0);  // Turn off UPD broadcast

  Serial.print(F("MAC: "));
  Serial.println(wifly.getMAC(buf, sizeof(buf)));
  Serial.print(F("IP: "));
  Serial.println(wifly.getIP(buf, sizeof(buf)));

  wifly.setDeviceID("Wifly-WebServer");

  if (wifly.isConnected()) {
    Serial.println(F("Old connection active. Closing"));
    wifly.close();
  }

  wifly.setProtocol(WIFLY_PROTOCOL_TCP);
  if (wifly.getPort() != 80) {
    wifly.setPort(80);
    /* local port does not take effect until the WiFly has rebooted (2.32) */
    wifly.save();
    Serial.println(F("Set port to 80, rebooting to make it work"));
    wifly.reboot();
    delay(3000);
  }
}
