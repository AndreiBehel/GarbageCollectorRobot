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
    
    wifly->sendChunkln(F("<!DOCTYPE html><html lang=\"en\"><head> <meta charset=\"UTF-8\"> <title"));
    wifly->sendChunkln(F(">Robot contol page</title> <style> .content { background-color: #f0f0f0"));
    wifly->sendChunkln(F("; max-width: 800px; margin: auto; text-align: center; border: 1px solid black"));
    wifly->sendChunkln(F("; padding: 0 20px; } .stat { box-sizing: border-box; padding: 10px 0; margin: 10px 10px"));
    wifly->sendChunkln(F("; width: 80px; height: 80px; border-radius: 10px 10px 0 0; display: inline-block"));
    wifly->sendChunkln(F("; font-family: 'Source Sans Pro', 'Helvetica Neue', Helvetica, Arial, sans-serif"));
    wifly->sendChunkln(F("; } .fullness { float: left; background: #ffcc5c; } .temp { background: #588c7e"));
    wifly->sendChunkln(F("; margin: 10px auto; } .charge { float: right; background: #d96459; } .table { margin: 20px"));
    wifly->sendChunkln(F("; padding: 10px 10px; border: 1px solid lightgray; } .left { clear: both"));
    wifly->sendChunkln(F("; float: left; } .right { float: right; } table { border-collapse: collapse"));
    wifly->sendChunkln(F("; } td { text-align: left; padding: 0px 20px; border-left: 1px solid #585858"));
    wifly->sendChunkln(F("; } th { text-align: left; padding: 10px; } caption { font-weight: bold"));
    wifly->sendChunkln(F("; border-bottom: 1px solid #585858; padding: 10px; } tr:nth-child(even"));
    wifly->sendChunkln(F(") { background: #ffeead; } .clearfix::after { content: \"\"; display: table"));
    wifly->sendChunkln(F("; clear: both; } .name { background: white; font-size: 14px; padding: 2px"));
    wifly->sendChunkln(F("; text-align: center; } .value { height: 40px; font-size: 22px; color: white"));
    wifly->sendChunkln(F("; } </style></head><body onload=\"stReq();\"><div class=\"content clearfix\""));
    wifly->sendChunkln(F("> <div class=\"important\"> <div class=\"stat fullness\"> <div class=\"value\""));
    wifly->sendChunkln(F(">100%</div> <div class=\"name\">Fullness</div> </div> <div class=\"stat charge\""));
    wifly->sendChunkln(F("> <div class=\"value\">50%</div> <div class=\"name\">Charge</div> </div"));
    wifly->sendChunkln(F("> <div class=\"stat temp\"> <div class=\"value\">21пїЅC</div> <div class=\"name\""));
    wifly->sendChunkln(F(">Temperature</div> </div> </div> <div class=\"left table\"> <table id=\"Rob\""));
    wifly->sendChunkln(F("> <caption>Robot data</caption> <tr> <th>Front IR sensor</th> <td>cm</td"));
    wifly->sendChunkln(F("> </tr> <tr> <th>Back IR sensor</th> <td>cm</td> </tr> <tr> <th>Charge level</th"));
    wifly->sendChunkln(F("> <td>%</td> </tr> <tr> <th>Temperature</th> <td>пїЅC</td> </tr> <tr> <th"));
    wifly->sendChunkln(F(">Fullness sensor</th> <td></td> </tr> <tr> <th>Moving</th> <td></td> </tr"));
    wifly->sendChunkln(F("> <tr> <th>Opened</th> <td></td> </tr> </table> </div> <div class=\"right table\""));
    wifly->sendChunkln(F("> <table id=\"Net\"> <caption>Network properties</caption> <tr> <th>Device id</th"));
    wifly->sendChunkln(F("> <td></td> </tr> <tr> <th>IP</th> <td></td> </tr> <tr> <th>Port</th> <td"));
    wifly->sendChunkln(F("></td> </tr> <tr> <th>Gateway</th> <td></td> </tr> <tr> <th>Netmask</th"));
    wifly->sendChunkln(F("> <td></td> </tr> <tr> <th>MAC</th> <td></td> </tr> <tr> <th>WiFi data rate</th"));
    wifly->sendChunkln(F("> <td>bits/sec</td> </tr> <tr> <th>Transmit power</th> <td>dBm</td> </tr"));
    wifly->sendChunkln(F("> <tr> <th>Time</th> <td></td> </tr> </table> </div></div><script> function stReq("));
    wifly->sendChunkln(F(") { setTimeout(reqNetInfo, 900); } function reqNetInfo() { try { var req = new XMLHttpRequest("));
    wifly->sendChunkln(F("); req.onreadystatechange = function () { if (this.readyState == 4 && this.status == 200 && this.responseText != null"));
    wifly->sendChunkln(F(") { let arr = this.responseText.split('&'); let table = window.document.getElementById('Net'"));
    wifly->sendChunkln(F("); arr.forEach((el, index) => { table.rows[index].cells[1].innerHTML = el.split('='"));
    wifly->sendChunkln(F(")[1] + table.rows[index].cells[1].innerHTML; }); var reqR = new XMLHttpRequest("));
    wifly->sendChunkln(F("); reqR.onreadystatechange = function () { if (this.readyState == 4 && this.status == 200 && this.responseText"));
    wifly->sendChunkln(F(") { let arr = this.responseText.split('&'); let table = window.document.getElementById('Rob'"));
    wifly->sendChunkln(F("); arr.forEach((el, index) => { table.rows[index].cells[1].innerHTML = el.split('='"));
    wifly->sendChunkln(F(")[1] + table.rows[index].cells[1].innerHTML; }); } }; reqR.open('GET', 'i', true"));
    wifly->sendChunkln(F("); reqR.send(); } }; req.open('GET', 'n', true); req.send(); } catch (ex"));
    wifly->sendChunkln(F(") { window.alert(ex); } }</script></body></html>"));
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
    byte code = wifly->multiMatch_P(20, 12, F("GET /f"), F("GET /b"), F("GET /w"), F("GET /s"),
    F("GET /m"), F("GET /o"), F("GET /k"), F("GET /t"), F("GET /c"), F("GET / "), F("GET /n"), F("GET /i"));
    
    switch(code) {
      case 0:
        Serial.println(F("#frIr"));
        send200(itoa(frIrSensor -> getCurrentValue(), buf, 10));
        break;
      case 1:
        Serial.println(F("#bcIr"));
        send200(itoa(bcIrSensor -> getCurrentValue(), buf, 10));
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
      case 10:
        Serial.println(F("#network"));
        send200(gatherNetworkInfo());
        break;
      case 11:
        Serial.println(F("#info"));
        send200(gatherRobotInfo());
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

char* HttpServer::gatherRobotInfo() {
  char data[150];
  sprintf(data,"frIr=%d&bcIr=%d&chr=%d&temp=%d&fullness=%d&mtr=%d&opSys=%d",
    frIrSensor -> getCurrentValue(),
    bcIrSensor -> getCurrentValue(),
    80,
    21,
    5,
    mt->moving(),
    opSystem->isOpened());
    
  return data;
}

char* HttpServer::gatherNetworkInfo() {
  char data[150];

  sprintf(data, "DevID=%s", wifly->getDeviceID(buf, sizeof(buf)));
  sprintf(data + strlen(data), "&IP=%s&Port=%d", wifly->getIP(buf, sizeof(buf)), wifly->getPort());
  sprintf(data + strlen(data), "&Mask=%s", wifly->getNetmask(buf, sizeof(buf)));
  sprintf(data + strlen(data), "&Gate=%s", wifly->getGateway(buf, sizeof(buf)));
  //sprintf(data + strlen(data), "&DNS=%s", wifly->getDNS(buf, sizeof(buf)));
  sprintf(data + strlen(data), "&MAC=%s&Rate=%lu&Pow=%d", wifly->getMAC(buf, sizeof(buf)), wifly->getRate(), wifly->getTxPower());
  sprintf(data + strlen(data), "&Time=%s", wifly->getTime(buf, sizeof(buf)));

  return data;
}
