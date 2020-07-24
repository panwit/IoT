#include <AIS_NB_BC95.h>
#include <ArduinoJson.h>

String serverIP = "161.246.38.104"; // Your Server IP
String serverPort = "1881"; // Your Server Port

String nodeName = "NB-IoT-001";

AIS_NB_BC95 AISnb;
String udpData;

const long interval = 10000;  //millisecond
unsigned long previousMillis = 0;

StaticJsonBuffer<200> jsonBuffer;
JsonObject& data = jsonBuffer.createObject();

long cnt = 0;
void setup()
{
  data["name"] = nodeName;

  AISnb.debug = true;
  
  Serial.begin(9600);
 
  AISnb.setupDevice(serverPort);

  String ip1 = AISnb.getDeviceIP();  
  delay(1000);
  
  pingRESP pingR = AISnb.pingIP(serverIP);
  previousMillis = millis();

}
void loop()
{ 
  udpData = "";
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
    {
      data["cnt"] = cnt++;

      data["s1"] = random(20,80);
      data["s2"] = random(30,70);
      data["test"] = "Test JSON";
      data["temp"] = 12.23;
      data["humid"] = 34.44;
      
      data.printTo(udpData);
      // Send data in String 
      UDPSend udp = AISnb.sendUDPmsgStr(serverIP, serverPort, udpData);
   
      //Send data in HexString     
      //udpDataHEX = AISnb.str2HexStr(udpData);
      //UDPSend udp = AISnb.sendUDPmsg(serverIP, serverPort, udpDataHEX);
      previousMillis = currentMillis;
  
    }
  UDPReceive resp = AISnb.waitResponse();
}