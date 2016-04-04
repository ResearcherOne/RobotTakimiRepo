/*
HC-SR04 Ping distance sensor]
VCC to arduino 5v GND to arduino GND
Echo to Arduino pin 12 Trig to Arduino pin 13
Red POS to Arduino pin 11
Green POS to Arduino pin 10
560 ohm resistor to both LED NEG and GRD power rail
More info at: http://goo.gl/kJ8Gl
Original code improvements to the Ping sketch sourced from Trollmaker.com
Some code and wiring inspired by http://en.wikiversity.org/wiki/User:Dstaub/robotcar
*/

#define trigPinSouth 6
#define trigPinNorth 8
#define trigPinWest 10
#define trigPinEast 12

#define echoPinSouth 7
#define echoPinNorth 9
#define echoPinWest 11
#define echoPinEast 13


void setup() {
  Serial.begin (9600);
  
  pinMode(trigPinEast, OUTPUT);
  pinMode(trigPinWest, OUTPUT);
  pinMode(trigPinSouth, OUTPUT);
  pinMode(trigPinNorth, OUTPUT);
  
  pinMode(echoPinEast, INPUT);
  pinMode(echoPinWest, INPUT);
  pinMode(echoPinSouth, INPUT);
  pinMode(echoPinNorth, INPUT);
}

long calculateDistance(int pinNum, int echoPinNum) {
  long duration, distance;
  digitalWrite(pinNum, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(pinNum, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(pinNum, LOW);
  duration = pulseIn(echoPinNum, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}

void loop() {
  long distanceEast = calculateDistance(trigPinEast, echoPinEast);
  long distanceWest = calculateDistance(trigPinWest, echoPinWest);
  long distanceSouth = calculateDistance(trigPinSouth, echoPinSouth);
  long distanceNorth = calculateDistance(trigPinNorth, echoPinNorth);
  
  Serial.println("New: East is "+String(distanceEast)+", West is "+String(distanceWest)+", South is "+String(distanceSouth)+", North is "+String(distanceNorth));
  delay(1000);
}
