#include "MessageSender.h"
MessageSender::MessageSender() {
  message = "";
}
void MessageSender::send() {
    Serial.print(message);
    message = "";
}
void MessageSender::update() {
   unsigned long currentMillis = millis();
    if((currentMillis - previousMillis >= intervalOfUpdate)) {
      send();
      previousMillis = currentMillis;
    }
}
void MessageSender::append(String command, String value) {
  message += "<" + command + "," + value + ">";
}

