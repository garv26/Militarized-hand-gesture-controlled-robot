#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#define button 7
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";


Adafruit_MPU6050 mpu;

void setup(void) {
 Serial.begin(115200);
 radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
pinMode(A0,INPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);
digitalWrite(5,HIGH);
digitalWrite(6,HIGH);
pinMode(3,OUTPUT);
digitalWrite(3,LOW);

 // Try to initialize!
 if (!mpu.begin()) {
  Serial.println("Failed to find MPU6050 chip");
  while (1) {
    delay(10);
  }
 }
 Serial.println("MPU6050 Found!");

 // set accelerometer range to +-8G
 mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

 // set gyro range to +- 500 deg/s
 mpu.setGyroRange(MPU6050_RANGE_500_DEG);

 // set filter bandwidth to 21 Hz
 mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

 delay(100);
}

void loop() {
 /* Get new sensor events with the readings */
 sensors_event_t a, g, temp;
 mpu.getEvent(&a, &g, &temp);

 /* Print out the values */
 Serial.print("Acceleration X: ");
 Serial.print(a.acceleration.x);
 Serial.print(", Y: ");
 Serial.print(a.acceleration.y);
 Serial.print(", Z: ");
 Serial.print(a.acceleration.z);
 Serial.println(" m/s^2");

 Serial.print("Rotation X: ");
 Serial.print(g.gyro.x);
 Serial.print(", Y: ");
 Serial.print(g.gyro.y);
 Serial.print(", Z: ");
 Serial.print(g.gyro.z);
 Serial.println(" rad/s");

 Serial.print("Temperature: ");
 Serial.print(temp.temperature);
 Serial.println(" degC");

 Serial.println("");
 int b=digitalRead(A0);
 if(b==0)
 {
 if(a.acceleration.x<-8)
 {
  radio.stopListening();
  int  buttonState =1;
    radio.write(&buttonState, sizeof(buttonState));
 }
 if(a.acceleration.x>8)
 {
  radio.stopListening();
  int  buttonState =-1;
    radio.write(&buttonState, sizeof(buttonState));
 }
 if(a.acceleration.y<-8)
 {
  radio.stopListening();
  int  buttonState =-2;
    radio.write(&buttonState, sizeof(buttonState));
 }
 if(a.acceleration.y>8)
 {
  radio.stopListening();
  int  buttonState =2;
    radio.write(&buttonState, sizeof(buttonState));
 }
 if(a.acceleration.x<8 && a.acceleration.x>-8 && a.acceleration.y>-8 && a.acceleration.y<8)  
 {
  radio.stopListening();
  int  buttonState =5;
    radio.write(&buttonState, sizeof(buttonState));
     Serial.println(" rad/s");

 }
 }
 if(b==1)
 {
  if(a.acceleration.x<-8)
 {
  radio.stopListening();
  int  buttonState =-3;
    radio.write(&buttonState, sizeof(buttonState));
 }
 if(a.acceleration.x>8)
 {
  radio.stopListening();
  int  buttonState =3;
    radio.write(&buttonState, sizeof(buttonState));
 }
 if(a.acceleration.x>-8 && a.acceleration.x<8)
 {
  radio.stopListening();
  int  buttonState =5;
    radio.write(&buttonState, sizeof(buttonState));
     Serial.println(" rad/s mn bmbj");
 }
 if(a.acceleration.y>8)
 {
  radio.stopListening();
  int  buttonState =0;
    radio.write(&buttonState, sizeof(buttonState));
 }
 }
 delay(50);
}