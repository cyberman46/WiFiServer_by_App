#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

ESP8266WebServer server;
char* ssid = "Akekapon Hotspot";
char* password = "akekapon.sp";
void setup() {
  pinMode(D7,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D5,OUTPUT);
  WiFi.begin(ssid,password);
  Serial.begin(115200);
  while(WiFi.status()!=WL_CONNECTED){
    Serial.print("*");
    delay(500);
  }

  Serial.println("");
  Serial.print(" IP Local: ");
  Serial.println(WiFi.localIP());

  server.on("/",[]{server.send(200,"text/plain","Hello World");});
  server.on("/LEDRedon",LEDRedon);
  server.on("/LEDWhiteon",LEDWhiteon);
  server.on("/LEDBlueon",LEDBlueon);
  server.on("/LEDRedoff",LEDRedoff);
  server.on("/LEDWhiteoff",LEDWhiteoff);
  server.on("/LEDBlueoff",LEDBlueoff);
  server.begin();

}

void LEDjson(){
  String status = server.arg("status");
  //String data = server.arg("plain");
  
  StaticJsonBuffer<200> jBuffer;
  JsonObject& jObject = jBuffer.parseObject(status);
  String msg = jObject["message"];
  server.send(200,"text/plain","Json : "+msg);
  Serial.print(msg);
}

void LEDstatus(){
  String status = server.arg("status");
  if (status == "HIGH"){
    digitalWrite(D7,HIGH);
  }else{
    digitalWrite(D7,LOW);
  }
  
  server.send(200,"text/plain","Status : "+status);  
}

void LEDRedon(){
  digitalWrite(D6,HIGH);
  server.send(200,"text/plain","Status : LED on");  
}

void LEDWhiteon(){
  digitalWrite(D7,HIGH);
  server.send(200,"text/plain","Status : LED on");  
}

void LEDBlueon(){
  digitalWrite(D5,HIGH);
  server.send(200,"text/plain","Status : LED on");  
}

////
void LEDRedoff(){
  digitalWrite(D6,LOW);
  server.send(200,"text/plain","Status : LED off");  
}

void LEDWhiteoff(){
  digitalWrite(D7,LOW);
  server.send(200,"text/plain","Status : LED off");  
}

void LEDBlueoff(){
  digitalWrite(D5,LOW);
  server.send(200,"text/plain","Status : LED off");  
}



void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
