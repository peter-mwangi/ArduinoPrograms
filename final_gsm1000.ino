#include<SoftwareSerial.h>
SoftwareSerial SIM900(7,8);
String textForSMS;
int pirsensor=6;
int tiltSensor;
int led=13;
int buzzer=12;
void setup(){
  Serial.begin(19200);
  SIM900.begin(19200);
  Serial.println("Logging time Completed");
  pinMode(pirsensor, INPUT);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(led, LOW);
  digitalWrite(buzzer, LOW);
  delay(5000);
}
void loop(){
  tiltSensor=analogRead(A0);
  if(tiltSensor<1022){
    textForSMS="\nIntruder Derected";
    digitalWrite(buzzer, HIGH);
    sendSMS(textForSMS);
    Serial.println(textForSMS);
    Serial.println("Message Sent");
    delay(1000);
    
  }
  if(digitalRead(pirsensor)==HIGH){  
    digitalWrite(led, HIGH);
    /*textForSMS="\nIntruder Derected";
    sendSMS(textForSMS);
    Serial.println(textForSMS);
    Serial.println("Message Sent");*/
    delay(1000);
    
  }
  else{
    digitalWrite(led, LOW);
    digitalWrite(buzzer, LOW);
    delay(1000);
    
  }
}
void sendSMS(String textForSMS){
  SIM900.print("AT+CMGF=1\r");
  delay(1000);
  SIM900.println("AT+CMGS=\"+254713382967\"\r");
  delay(1000);
  SIM900.println(textForSMS);
  delay(1000);
  SIM900.println((char)26);
  delay(1000);
  SIM900.println();
  delay(1000);
}
