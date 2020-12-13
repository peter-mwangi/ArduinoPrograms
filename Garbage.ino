#include<LiquidCrystal.h>
#include<SoftwareSerial.h>
SoftwareSerial SIM900(1,10);
String textForSMS;
#define trigger 9
#define echo 8
LiquidCrystal lcd(2,3,4,5,6,7);
float time=0,distance=0;
const int LED1 = 11; // the LEDI is connected to pin 11
const int LED2 = 12;
const int LED3 = 13;
//const int LED4 = 0;
void setup()
{
    Serial.begin(19200);
  SIM900.begin(19200);
  Serial.println("Logging time Completed");
  
  pinMode(trigger,OUTPUT); // set the trigger pin as an output
 pinMode(echo,INPUT); // set the echo pin as an input
 pinMode(LED1, OUTPUT);// set the relay pin as an output
 pinMode(LED2, OUTPUT);
 pinMode(LED3, OUTPUT);
 // pinMode(LED4, OUTPUT);
  lcd.begin(16, 2);
 lcd.setCursor(2,0);
 lcd.print("GABAGE MONITORING");
 lcd.setCursor(1,1);
 lcd.print("CONTROL SYSTEM");
 delay(2000);
}
void loop()
{
   lcd.clear();
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 digitalWrite(trigger,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigger,LOW);
 delayMicroseconds(2);
 time=pulseIn(echo,HIGH); // stores the time span between the transmitted and reflected waves
 distance=time*0.034/2; //formula to calculate the distance in cm
 lcd.setCursor(0,0);
 lcd.print("GABBAGE:");
 lcd.setCursor(0,1);
 lcd.print("LEVEL:");
 delay(10);
 if(distance>=40.00)
 {
  digitalWrite(LED1, HIGH);
   digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  delay(100);
   lcd.setCursor(8,0);
   lcd.print("LOW");
   lcd.setCursor(7,1);
   lcd.print("NO GABBAGE TO BE COLLECTED");
   textForSMS="\nNO GABBAGE";
    sendSMS(textForSMS);
    sendSMS1(textForSMS);
    sendSMS2(textForSMS);
    Serial.println(textForSMS);
    Serial.println("Message Sent");
    delay(100);
  //delay(1000);
 }
 else{
  digitalWrite(LED1, LOW);
 }
 /* if(distance<20.00 && distance >10)
 {
   digitalWrite(LED2,HIGH);
   lcd.setCursor(7,0);
   lcd.print("STILL LOW");
   lcd.setCursor(7,1);
   lcd.print("GABAGE IS ACCUMULATING");
   delay(1000);
 }
else{
  digitalWrite(LED2, LOW);
 }*/
  if(distance<40.00 && distance >20)
 {
   digitalWrite(LED2, HIGH);
   digitalWrite(LED1, LOW);
    digitalWrite(LED3, LOW);
   delay(100);
   lcd.setCursor(7,0);
   lcd.print("MEDIUM");
   lcd.setCursor(7,1);
   lcd.print("GABBAGE IS HALFWAY");
   textForSMS="\nALERT!!!\nGABBAGE HALF WAY FULL\nLOCATION IS:\nhtpp:www.tai";
   sendSMS(textForSMS);
    sendSMS1(textForSMS);
    sendSMS2(textForSMS);
    Serial.println(textForSMS);
    Serial.println("Message Sent");
    delay(100);
   //delay(1000);

 }
 else{
  digitalWrite(LED2, LOW);
 }
  if(distance<=10.00)// check if GABAGE is full
 {
  digitalWrite(LED3, HIGH);
  digitalWrite(LED2, LOW);
    digitalWrite(LED1, LOW);
  delay(100);
   lcd.setCursor(7,0);
   lcd.print("FULL");
   lcd.setCursor(7,1);
   lcd.print("GABBAGE SHOULD BE COLECTED");
   textForSMS="\nGABAGE ALMOST FULL\nIT SHOULD BE COLLECTED";
    sendSMS(textForSMS);
    sendSMS1(textForSMS);
    sendSMS2(textForSMS);
    Serial.println(textForSMS);
    Serial.println("Message Sent");
    //delay(100);
   delay(100);
 }
 else{
  digitalWrite(LED3, LOW);
 }
 //delay(100);
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
void sendSMS1(String textForSMS){
  SIM900.print("AT+CMGF=1\r");
  delay(1000);
  SIM900.println("AT+CMGS=\"+254713696289\"\r");
  delay(1000);
  SIM900.println(textForSMS);
  delay(1000);
  SIM900.println((char)26);
  delay(1000);
  SIM900.println();
  delay(1000);
}
void sendSMS2(String textForSMS){
  SIM900.print("AT+CMGF=1\r");
   delay(1000);
  SIM900.println("AT+CMGS=\"+254745750401\"\r");
    delay(1000);
  SIM900.println(textForSMS);
    delay(1000);
  SIM900.println((char)26);
    delay(1000);
  SIM900.println();
  delay(1000);
}
