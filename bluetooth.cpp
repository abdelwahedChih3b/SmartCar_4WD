#include <SR04.h>

#define trig_pin 13   //trig at pin 13
#define echo_pin 12 //echo at pin 12
SR04 sr04 = SR04(echo_pin,trig_pin);
int distance =0 ;  //variable pour stocker la distance
void loop(){
distance  = sr04.Distance();
Serial.println(distance);
delay(500)
}