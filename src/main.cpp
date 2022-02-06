#include <Arduino.h>



//Setup for Ultrasonic sensor

#include <SR04.h>

#define trig_pin 13
#define echo_pin 12

SR04 sr04 = SR04(echo_pin,trig_pin);
char p_command ;
//Setup for Servo Motor

#include <Servo.h>

Servo myservo;

int pos = 0;
int leftDis = 0;
int rightDis = 0;
int forward = 0;

//Setup for Wheel Motors


#define in1 7
#define in2 5

#define in3 4
#define in4 2

void go() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("go");
}
void reverse() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("reverse");
}

void left() {

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void right() {

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void setup() {
  
  Serial.begin(9600);
  myservo.attach(11);  //servo pin is set at 11

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
 
}

void loop() {

  if(Serial.available() > 0){
    p_command = Serial.read();
 

 if (p_command == 'F') {
  go(); // Turn LED OFF
  Serial.println("go"); // Send back, to the phone
  p_command = NULL;
 }
 else if (p_command == 'B') {
  reverse();
  Serial.println("reverse");
  p_command = NULL;
 } 
 else if (p_command == 'R') {
  right();
  Serial.println("right");
  p_command = NULL;
 }
  else if (p_command == 'L') {
  left();
  Serial.println("left");
  p_command = NULL;
 }
 else if (p_command == 'S') {
  stop();
  Serial.println("left");
  p_command = NULL;
 }
 delay(100);
 }
 else if (p_command == 'Z') {
  myservo.write(90); //set servo at 90 angle 
  delay(100);
  
  forward = sr04.Distance(); 
  Serial.println(forward);

  if (forward < 15) {
    stop();
    delay(500);
    reverse();
    delay(20);

    myservo.write(10);
    delay(500);
    rightDis = sr04.Distance();
    delay(100) ;
    Serial.println(leftDis);

    myservo.write(170);
    delay(500);
    leftDis = sr04.Distance();
    delay(100);
    Serial.println(rightDis);

    if(rightDis > leftDis ) {
        if (rightDis > 15)
        {
          
          right();
          delay(20); 
        }
        
        
      }
      else if(rightDis < leftDis ) {
        if (leftDis > 15)
        {
          left();
          delay(15);
        }
        
        else
        {
          reverse();
          delay(15);
        }
        
      }
      
      myservo.write(90);
      delay(500);
  }
  
  else{
    go();
  }}
  
}