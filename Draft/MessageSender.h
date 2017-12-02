#ifndef MESSAGESENDER_H
  #define MESSAGESENDER_H
#include <Arduino.h>
class MessageSender {
private:
  long intervalOfUpdate;
  unsigned long previousMillis;
  String message;
public:
  MessageSender();
  void append(String command, String value);
  void send();
  void update();
};
#endif
