#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
#include<Servo.h>
#include  <SPI.h>
Servo myservo;
RF24 radio(7,8); // CE, CSN
const byte address[6] = "00001";
int buttonstate;
int s=90;


void setup() {
pinMode(A0,OUTPUT);
digitalWrite(A0,HIGH);

pinMode(A1,OUTPUT);
digitalWrite(A1,LOW);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
pinMode(A4,OUTPUT);
pinMode(A5,OUTPUT);
myservo.attach(3);
Serial.begin(9600);
radio.begin();
radio.openReadingPipe(0, address);
radio.setPALevel(RF24_PA_MAX);
radio.startListening();
myservo.write(s);
}
void loop() {
radio.startListening();
while (!radio.available());
radio.read(&buttonstate, sizeof(buttonstate));
Serial.println(buttonstate);
if(buttonstate==1)
{
  digitalWrite(5,HIGH);//right forward
  digitalWrite(A4,HIGH);//left forward
  digitalWrite(6,LOW);//right backward
  digitalWrite(A5,LOW);//left backward
}

if(buttonstate==-1)
{
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(A4,LOW);
  digitalWrite(A5,HIGH);
}
if(buttonstate==2)
{
  digitalWrite(5,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(A4,HIGH);
  digitalWrite(A5,LOW);
}
if(buttonstate==-2)
{
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
  digitalWrite(A4,LOW);
  digitalWrite(A5,HIGH);
}
if(buttonstate==5)
{
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(A4,LOW);
  digitalWrite(A5,LOW);
}
if (buttonstate==3)
{
  
  
    myservo.write(25);
    }
if(buttonstate==-3)
{
  
  
  myservo.write(140);
  
}
if(buttonstate==0)
{
  myservo.write(90);
}
}