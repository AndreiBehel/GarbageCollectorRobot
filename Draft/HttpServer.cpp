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

/** Send a greeting HTML page with the user's name and an analog reading */
void HttpServer::sendGreeting(char *name)
{
    /* Send the header directly with print */
    wifly->println(F("HTTP/1.1 200 OK"));
    wifly->println(F("Content-Type: text/html"));
    wifly->println(F("Transfer-Encoding: chunked"));
    wifly->println();

    /* Send the body using the chunked protocol so the client knows when
     * the message is finished.
     */
    wifly->sendChunkln(F("<html>"));
    wifly->sendChunkln(F("<title>WiFly HTTP Server Example</title>"));
    /* No newlines on the next parts */
    wifly->sendChunk(F("<h1><p>Hello "));
    wifly->sendChunk(name);
    /* Finish the paragraph and heading */
    wifly->sendChunkln(F("</p></h1>"));

    /* Include a reading from Analog pin 0 */
    snprintf_P(buf, sizeof(buf), PSTR("<p>Analog0=%d</p>"), analogRead(A0));
    wifly->sendChunkln(buf);

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
    wifly->println(F("Transfer-Encoding: chunked"));
    wifly->println();
    
    wifly->sendChunkln(str);
    wifly->sendChunkln();
}

void HttpServer::receive()
{
  if (wifly->available() > 0) {
    /* See if there is a request */
    if (wifly->gets(buf, sizeof(buf))) {
      //Request for index page
      if (strncmp_P(buf, PSTR("GET / "), 6) == 0) {
        wifly->flushRx();       
        sendIndex();
        
      } else if (strncmp_P(buf, PSTR("GET /f"), 6) == 0) {
        wifly->flushRx();      
        send200(dtostrf(frIrSensor -> getCurrentValue(), 0, 2, convBuff));
        
      } else if (strncmp_P(buf, PSTR("GET /b"), 6) == 0) {
        wifly->flushRx();      
        send200(dtostrf(bcIrSensor -> getCurrentValue(), 0, 2, convBuff));
        
      } else if (strncmp_P(buf, PSTR("GET /c"), 6) == 0) {
        wifly->flushRx();
        send200(dtostrf(battery -> level(), 0, 2, convBuff));
        
      } else if (strncmp_P(buf, PSTR("GET /t"), 6) == 0) {
        wifly->flushRx();   
        send200(dtostrf(20.3, 0, 2, convBuff));
        
      }  else if (strncmp_P(buf, PSTR("GET /p"), 6) == 0) {
        wifly->flushRx();   
        send200(dtostrf(59, 0, 2, convBuff));
        
      } else if (strncmp_P(buf, PSTR("GET /w"), 6) == 0) {
        wifly->flushRx();
        getTime(buf, 7);
        mt -> moveFr(2000);
      } else if (strncmp_P(buf, PSTR("GET /s"), 6) == 0) {
        wifly->flushRx();
        getTime(buf, 7);
        mt -> moveBc(2000);
      } else if (strncmp_P(buf, PSTR("GET /m"), 6) == 0) {
        wifly->flushRx();

        if(parseReqStr(buf, params)) {
          mt -> move(params[0], params[1], params[2], params[3], params[4]);
        } else {
          send404();
        }
        
      } else if (strncmp_P(buf, PSTR("GET /o"), 6) == 0) {
        wifly->flushRx();
        opSystem -> Open();
        
      } else if (strncmp_P(buf, PSTR("GET /k"), 6) == 0) {
        wifly->flushRx();
        opSystem -> Close();
        
      } else {
        /* Unexpected request */
        Serial.print(F("Unexpected: "));
        Serial.println(buf);
        wifly->flushRx();    // discard rest of input
        Serial.println(F("Sending 404"));
        send404();
      }
    }
  }
}
/*get time from a string of GET request  
 * GET /w?t=10&nocache=29860.903564600583 HTTP/1.1
 */
int HttpServer::getTime(char* str, byte pos) {
  int time = -1;
  String strNum = "";
  
  if(str[pos++] == 't' && str[pos++] == '=' && isDigit(str[pos])) {
    while(isDigit(str[pos])) {
      strNum += str[pos++];
    }
    time = strNum.toInt();
  }
  
  return time;
}

bool HttpServer::parseReqStr(char* str, byte* params) {
  bool correct = true; 
  byte pos = 7;
  String strNum = "";
  
  if(str[pos++] == 'l' && str[pos++] == '=' && isDigit(str[pos])) {
    while(isDigit(str[pos])) {
      strNum += str[pos++];
    }
    params[0] = strNum.toInt();
  } else { 
    correct = false;
  }
  
  if(str[pos++] == '&' && str[pos++] == 'd' && str[pos++] == '=' && isDigit(str[pos])) {
    str = "" + str[pos++];
    params[1] = strNum.toInt();
  } else { 
    correct = false;
  }

  if(str[pos++] == '&' && str[pos++] == 'r' && str[pos++] == '=' && isDigit(str[pos])) {
    str = "";
    while(isDigit(str[pos])) {
      strNum += str[pos++];
    }
    params[2] = strNum.toInt();
  } else { 
    correct = false;
  }

  if(str[pos++] == '&' && str[pos++] == 'd' && str[pos++] == '=' && isDigit(str[pos])) {
    str = "" + str[pos++];
    params[3] = strNum.toInt();
  } else { 
    correct = false;
  }

  if(str[pos++] == '&' && str[pos++] == 't' && str[pos++] == '=' && isDigit(str[pos])) {
    str = "";
    while(isDigit(str[pos])) {
      strNum += str[pos++];
    }
    params[4] = strNum.toInt();
  } else { 
    correct = false;
  }
  
  return correct;
}

