#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D2 //กำหนดว่าขาของเซนเซอร์ 18B20 ต่อกับขา 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
float tem1;
float tem2;
const char* ssid = "JOUWG";
const char* pass = "818291903";
char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "1YKN3HMOQ1VVCXPR";
WiFiClient client;
void setup() {
  // put your setup code here, to run once:
  pinMode(D3,OUTPUT);
  pinMode(D1,OUTPUT);
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);  
  }
  Serial.println(""); 
  Serial.println("Wi-Fi connected");
  Serial.print("IP : ");
  Serial.println(WiFi.localIP());
  Serial.println("เริ่มต้นการวัดอุณหภูมิ");
  sensors.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
  sensors.requestTemperatures(); //สั่งอ่านค่าอุณหภูมิ
  tem1 = sensors.getTempCByIndex(0);
  tem2 = sensors.getTempCByIndex(0);
  if(tem1 > 30){
    digitalWrite(D3,HIGH);
    Serial.print(tem1, 2);
    Serial.println(" องศาเซลเซียส");
    Serial.println("อุณหภูมิค่อนข้างร้อน");
    delay(1000);
    digitalWrite(D3,LOW);
    delay(1000);
    String temper1 = (String) tem1;
    String data = "field1=" + temper1;
    if (client.connect(thingSpeakAddress, 80)) {
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data.length());
    client.print("\n\n");
    client.print(data);
  }
    delay(1000);}else if(tem1 < 26){
      digitalWrite(D1,HIGH);
      Serial.print(tem1, 2);
      Serial.println(" องศาเซลเซียส");
      Serial.println("อุณหภูมค่อนข้างเย็น");
      delay(1000);
      digitalWrite(D1,LOW);
      delay(1000);
      String temper1 = (String) tem1;
      String data = "field1=" + temper1;
      if (client.connect(thingSpeakAddress, 80)) {
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(data.length());
        client.print("\n\n");
        client.print(data);
  }
  delay(1000);}else if(tem1<=30&&tem1>=26){
      Serial.print(tem1, 2);
      Serial.println(" องศาเซลเซียส");
      Serial.println("อุณหภูมเหมาะสม");
      delay(1000);
      digitalWrite(D1,LOW);
      digitalWrite(D3,LOW);
      delay(1000);
      String temper1 = (String) tem1;
      String data = "field1=" + temper1;
      if (client.connect(thingSpeakAddress, 80)) {
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(data.length());
        client.print("\n\n");
        client.print(data);
    }
  delay(1000);}
}
