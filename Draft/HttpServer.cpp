#include "HttpServer.h"

HttpServer::HttpServer(Motor* m, OpSystem* o, IRSensor* f, IRSensor* b, Battery* bat, WiFly* w) 
{
	mt = m;
  opSystem = o;
  
  frIrSensor = f;
  bcIrSensor = b;

  battery = bat;
  
  wifly = w;
}

/** Send an index HTML page*/
void HttpServer::sendIndex()
{
   /* Send the header direclty with print */
    wifly->println(F("HTTP/1.1 200 OK"));
    wifly->println(F("Content-Type: text/html"));
    wifly->println(F("Transfer-Encoding: chunked"));
    wifly->println(F("Connection: keep-alive"));
    wifly->println();
    
    wifly->sendChunkln(F("<!DOCTYPE html>"));
    wifly->sendChunkln(F("<html lang=\"en\">"));
    wifly->sendChunkln(F("<head>"));
    wifly->sendChunkln(F("<meta charset=\"UTF-8\">"));
    wifly->sendChunkln(F("<title>Garbage Collector Robot</title>"));
    
    wifly->sendChunkln(F("<script>"));
    wifly->sendChunkln(F("function GetFrIrSensor() {"));
    wifly->sendChunkln(F("nocache = \"&nocache=\" + Math.random() * 1000000;"));
    wifly->sendChunkln(F("var request = new XMLHttpRequest();"));
    wifly->sendChunkln(F("request.onreadystatechange = function () {"));
    wifly->sendChunkln(F("if (this.readyState == 4 && this.status == 200) {"));
    wifly->sendChunkln(F("if (this.responseText != null) {"));
    wifly->sendChunkln(F("document.getElementById(\"frIRSensor\").innerHTML = this.responseText;"));
    wifly->sendChunkln(F("}}}"));
    wifly->sendChunkln(F("request.open(\"GET\", \"f\" + nocache, true);"));
    wifly->sendChunkln(F("request.send(null);"));
    wifly->sendChunkln(F("setTimeout('GetFrIrSensor()', 3000);"));

    wifly->sendChunkln(F("};function GetBcIrSensor() {"));
    wifly->sendChunkln(F("nocache = \"&nocache=\" + Math.random() * 1000000;"));
    wifly->sendChunkln(F("var request = new XMLHttpRequest();"));
    wifly->sendChunkln(F("request.onreadystatechange = function () {"));
    wifly->sendChunkln(F("if (this.readyState == 4 && this.status == 200) {"));
    wifly->sendChunkln(F("if (this.responseText != null) {"));
    wifly->sendChunkln(F("document.getElementById(\"bcIRSensor\").innerHTML = this.responseText;"));
    wifly->sendChunkln(F("}}}"));
    wifly->sendChunkln(F("request.open(\"GET\", \"b\" + nocache, true);"));
    wifly->sendChunkln(F("request.send(null);"));
    wifly->sendChunkln(F("setTimeout('GetBcIrSensor()', 3000);"));
    
    wifly->sendChunkln(F("};</script>"));
    wifly->sendChunkln(F("</head>"));
    wifly->sendChunkln(F("<body onload=\"GetFrIrSensor(); GetBcIrSensor();\">"));
    wifly->sendChunkln(F("<p><b>Front distance: </b><span id=\"frIRSensor\">Not requested</span></p>"));
    wifly->sendChunkln(F("<p><b>Back distance:</b><span id=\"bcIRSensor\"> Not requested</span></p>"));
    wifly->sendChunkln(F("</body>"));
    wifly->sendChunkln(F("</html>"));
    wifly->sendChunkln();
}

/** Send a 404 error */
void HttpServer::send404()
{
    wifly->println(F("HTTP/1.1 404 Not Found"));
    wifly->println(F("Content-Type: text/html"));
    wifly->println(F("Transfer-Encoding: chunked"));
    wifly->println();
    
    wifly->sendChunkln(F("<html><head>"));
    wifly->sendChunkln(F("<title>404 Not Found</title>"));
    wifly->sendChunkln(F("</head><body>"));
    wifly->sendChunkln(F("<h1>Not Found</h1>"));
    wifly->sendChunkln(F("<hr>"));
    wifly->sendChunkln(F("</body></html>"));
    wifly->sendChunkln();
}

void HttpServer::send200(char* str)
{
    wifly->println(F("HTTP/1.1 200 OK"));
    wifly->println(F("Content-Type: text/html"));
    wifly->println(F("Connection: close"));
    //wifly->println(F("Cache-Control: no-cache"));
    wifly->println(F("Transfer-Encoding: chunked"));
    wifly->println();
    
    wifly->sendChunkln(str);
    wifly->sendChunkln();
}

void HttpServer::receive()
{
  if (wifly->available() > 0) {
    byte code = wifly->multiMatch_P(20, 10, F("GET /f"), F("GET /b"), F("GET /w"), F("GET /s"),
    F("GET /m"), F("GET /o"), F("GET /k"), F("GET /t"), F("GET /c"), F("GET / "));
    
    switch(code) {
      case 0:
        Serial.println(F("#frIr"));
        send200(dtostrf(frIrSensor -> getCurrentValue(), 0, 2, convBuff));
        break;
      case 1:
        Serial.println(F("#bcIr"));
        send200(dtostrf(bcIrSensor -> getCurrentValue(), 0, 2, convBuff));
        break;
      case 2:
        Serial.println(F("#w"));
        wifly->gets(buf, sizeof(buf), 10);
        mt -> moveFr(getTime(buf, 1) * 100);
        send200(NULL);
        break;
      case 3:
        Serial.println(F("#s"));
        wifly->gets(buf, sizeof(buf), 10);
        mt -> moveBc(getTime(buf, 1) * 100);
        send200(NULL);
        break;
      case 4:
        Serial.println(F("#move"));
        wifly->gets(buf, sizeof(buf), 10);
        if(parseReqStr(buf, params, 1)) {
          mt -> move(params[0], params[1], params[2], params[3], params[4] * 100);
          send200(NULL);
        } else {
          send404();
        }
        break;
      case 5:
        Serial.println(F("#open"));
        opSystem -> Open();
        send200(NULL);
        break;
      case 6:
        Serial.println(F("#close"));
        opSystem -> Close();
        send200(NULL);
        break;
      case 7:
        Serial.println(F("#temperature"));
        send200(dtostrf(21.2, 0, 2, convBuff));
        break;
      case 8:
        Serial.println(F("#charge"));
        send200(dtostrf(83.5, 0, 2, convBuff));
        break;
      case 9:
        Serial.println(F("#page"));
        sendIndex();
        break;
      default: /* timeout */
        //Serial.println("#timeout");
        break;
    }
  }
}

/*get time from a string of GET request  
 * GET /w?t=10&nocache=29860.903564600583 HTTP/1.1
 */
byte HttpServer::getTime(char* str, byte pos) {
  byte time = 0;
  String strNum = "";
  
  if(str[pos++] == 't' && str[pos++] == '=' && isDigit(str[pos])) {
    while(isDigit(str[pos])) {
      strNum += str[pos++];
    }
    time = strNum.toInt();
  }
  
  if(!time) {
    time = 10;
  }
  return time;
}

/*Processing of moving request
 *GET /m?a=0&b=255&c=0&d=255&t=30
 *http://192.168.43.3/m?a=1&b=255&c=0&d=255&t=30
 */
bool HttpServer::parseReqStr(char* str, byte* params, byte pos) {
  bool correct = true; 
  String strNum = "";

  if(str[pos++] == 'a' && str[pos++] == '=' && isDigit(str[pos])) {
    strNum += str[pos++];
    params[0] = strNum.toInt();
  } else { 
    correct = false;
  }
  
  if(str[pos++] == '&' && str[pos++] == 'b' && str[pos++] == '=' && isDigit(str[pos])) {
    strNum = "";
    while(isDigit(str[pos])) {
      strNum += str[pos++];
    }
    params[1] = strNum.toInt();
  } else { 
    correct = false;
  }

  if(str[pos++] == '&' && str[pos++] == 'c' && str[pos++] == '=' && isDigit(str[pos])) {
    strNum = "";
    strNum += str[pos++];
    params[2] = strNum.toInt();
  } else { 
    correct = false;
  }
  
  if(str[pos++] == '&' && str[pos++] == 'd' && str[pos++] == '=' && isDigit(str[pos])) {
    strNum = "";
    while(isDigit(str[pos])) {
      strNum += str[pos++];
    }
    params[3] = strNum.toInt();
  } else { 
    correct = false;
  }

  if(str[pos++] == '&' && str[pos++] == 't' && str[pos++] == '=' && isDigit(str[pos])) {
    strNum = "";
    while(isDigit(str[pos])) {
      strNum += str[pos++];
    }
    params[4] = strNum.toInt();
  } else { 
    correct = false;
  }
  
  return correct;
}

