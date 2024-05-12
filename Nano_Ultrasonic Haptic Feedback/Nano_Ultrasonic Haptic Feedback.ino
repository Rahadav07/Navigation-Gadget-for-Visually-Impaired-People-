
#define trigPin1 14 //attach pin D3 Arduino to pin Trig of HC-SR04
#define trigPin2 4 //attach pin D5 Arduino to pin Trig of HC-SR04
#define echoPin1 15 // attach pin D4 Arduino to pin Echo of HC-SR04
#define echoPin2 5 // attach pin D6 Arduino to pin Echo of HC-SR04
#define haptic1 6 
#define haptic2 7
// #define haptic3 11
#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"
// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
  unsigned long StartTime1=0;
  unsigned long StartTime2=0;
  // unsigned long StartTime3=0;
  unsigned long time_arr[]={StartTime1,StartTime2}; //,StartTime3
  
  ///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);

void setup() {
  pinMode(trigPin1, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(trigPin2, OUTPUT); // Sets the trigPin as an OUTPUT
  // pinMode(trigPin3, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin1, INPUT); // Sets the echoPin as an INPUT
  pinMode(echoPin2, INPUT); // Sets the echoPin as an INPUT
  // pinMode(echoPin3, INPUT); // Sets the echoPin as an INPUT
  pinMode(haptic1,OUTPUT);
  pinMode(haptic2,OUTPUT);
  digitalWrite(haptic1,HIGH);
  digitalWrite(haptic2,HIGH);
  // pinMode(haptic3,OUTPUT);
  Serial.begin(2400); // // Serial Communication is starting with 9600 of baudrate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}
void short_pulse(uint8_t haptic_pin){
   
   digitalWrite(haptic_pin, LOW);
   delay(100);
   digitalWrite(haptic_pin,HIGH);
   delay(80);
  
}
void med_pulse(uint8_t haptic_pin ){
  
   digitalWrite(haptic_pin, LOW);
   delay(200);
   digitalWrite(haptic_pin ,HIGH);
   delay(130);
   
}
void long_pulse(uint8_t haptic_pin){
   
   digitalWrite(haptic_pin , LOW);
   delay(300);
   digitalWrite(haptic_pin ,HIGH);
   delay(200);
  
}

int cal_dist(uint8_t trigPin,uint8_t echoPin){

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}


void loop() {

  unsigned long currentTime=millis();

  int dis1=cal_dist(trigPin1,echoPin1);
  int dis2=cal_dist(trigPin2,echoPin2);
  // int dis3=cal_dist(trigPin3,echoPin3);
 
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(dis1);
  Serial.print(" cm ");
  Serial.print(" ");
  Serial.print(dis2);
  Serial.println(" cm ");
  // Serial.print("");
  // Serial.print(dis3);
  // Serial.println(" cm ");

  uint8_t haptic_arr[]={haptic1,haptic2}; //HAPTIC3
  int dis_arr[]={dis1,dis2}; //DIS3
  int arr_size=sizeof(dis_arr)/sizeof(dis_arr[0]);

  for (int i=0;i<2;i++) {
    if(dis_arr[i]==0){
      continue;
    }
    else if(dis_arr[i]<10){
    short_pulse(haptic_arr[i]);
    }
    else if(dis_arr[i]<30){
    med_pulse(haptic_arr[i]);
    }
    else if(dis_arr[i]<50) {
      if(currentTime-time_arr[i]>=4000){
        for(int j=0;j<3;j++){
          long_pulse(haptic_arr[i]);
          }
        time_arr[i]=currentTime;  
      }
    }
  }
 
}
//  if(currentTime-StartTime>=2000){
//    StartTime=currentTime;              
//       }