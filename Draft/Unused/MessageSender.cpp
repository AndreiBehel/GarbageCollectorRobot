#include "MessageSender.h"
MessageSender::MessageSender(IRSensor* f, IRSensor* b, Battery* bat) {
  frIrSensor = f;
  bcIrSensor = b;
  battery = bat;
  
  battery -> begin();
  
  intervalOfUpdate = 500;
  irSendInterval = 1000;
  fulnessSendInterval = 60000;
  tempSendInterval = 60000;
  batterySendInterval = 65000;
  message = "";
}

void MessageSender::send() {
    Serial.println(message);
    message = "";
}

void MessageSender::Update() {
   unsigned long currentMillis = millis();
    if((currentMillis - previousMillis >= intervalOfUpdate)) {
      send();
      previousMillis = currentMillis;
    }
    if((currentMillis - irPrevMillis >= irSendInterval)) {
      addIRData();
      irPrevMillis = currentMillis;
    }
    if((currentMillis - fullnessPrevMillis >= fulnessSendInterval)) {
      addFullnessData();
      fullnessPrevMillis = currentMillis;
    }
    if((currentMillis - tempPrevMillis >= tempSendInterval)) {
      addTempData();
      tempPrevMillis = currentMillis;
    }
}

void MessageSender::add(String m) {
  message += m;
}

void MessageSender::addIRData() {
  message += "<f," + String(frIrSensor -> getCurrentValue(), 1) + ">";
  message += "<b," + String(bcIrSensor -> getCurrentValue(), 1) + ">";
}

void MessageSender::addFullnessData() {
  message += "<e,5>";
}

void MessageSender::addTempData() {
  message += "<t,22>";
}

void MessageSender::addBatteryData() {
  message += "<p,95>";
  //message += "<p," + String(battery.level());
}

void MessageSender::setIrSendInterval(unsigned int v) {
  irSendInterval = v;
}

void MessageSender::setFullnessSendInterval(unsigned int v) {
  fulnessSendInterval = v;
}

void MessageSender::setTempSendInterval(unsigned int v) {
  tempSendInterval = v;
}

void MessageSender::setBatterySendInterval(unsigned int v) {
  batterySendInterval = v;
}
