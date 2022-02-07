void setup() 
{
Serial.begin(9600); // activates Serial Communication
}

void loop() 
{
Serial.print(digitalRead(8)); // Line Tracking sensor is connected with pin 8 of the Arduino
delay(500);
}