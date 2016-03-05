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

#define trigPinsouth 6
#define echoPinsouth 7
#define trigPinnorth 8
#define echoPinnorth 9
#define trigPinwest 10
#define echoPinwest 11
#define trigPineast 12
#define echoPineast 13


void setup() {
  Serial.begin (9600);
  pinMode(trigPineast, OUTPUT);
  pinMode(echoPineast, INPUT);
  pinMode(trigPinwest, OUTPUT);
  pinMode(echoPinwest, INPUT);
  pinMode(trigPinsouth, OUTPUT);
  pinMode(echoPinsouth, INPUT);
  pinMode(trigPinnorth, OUTPUT);
  pinMode(echoPinnorth, INPUT);
}

void loop() {
  long durationeast, distanceeast;
  digitalWrite(trigPineast, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPineast, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPineast, LOW);
  durationeast = pulseIn(echoPineast, HIGH);
  distanceeast = (durationeast/2) / 29.1;
  /*if (distanceeast >= 200 || distanceeast <= 0){
    Serial.println("East is out of range");
    //Serial.println("Out of range");
  }
  else {
    Serial.println("East is " + String(distanceeast));
    //Serial.print(distanceeast);
    //Serial.println(" cm");
  }
  delay(500); */
  long durationwest, distancewest;
  digitalWrite(trigPinwest, LOW);
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinwest, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinwest, LOW);
  durationwest = pulseIn(echoPinwest, HIGH);
  distancewest = (durationwest/2) / 29.1;
  /*if (distancewest >= 200 || distancewest <= 0){
    Serial.println("West is out of range");
    //Serial.println("Out of range");
  }
  else {
    Serial.println("West is " + String(distancewest));
    //Serial.print(distancewest);
    //Serial.println(" cm");
  }
  delay(500); */
  long durationsouth, distancesouth;
  digitalWrite(trigPinsouth, LOW);
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinsouth, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinsouth, LOW);
  durationsouth = pulseIn(echoPinsouth, HIGH);
  distancesouth = (durationsouth/2) / 29.1;
  /*if (distancesouth >= 200 || distancesouth <= 0){
    Serial.println("South is out of range");
    //Serial.println("Out of range");
  }
  else {
    Serial.println("South is " + String(distancesouth));
    //Serial.print(distancesouth);
    //Serial.println(" cm");
  }
  delay(500); */
  long durationnorth, distancenorth;
  digitalWrite(trigPinnorth, LOW);
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinnorth, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinnorth, LOW);
  durationnorth = pulseIn(echoPinnorth, HIGH);
  distancenorth = (durationnorth/2) / 29.1;
  /*if (distancenorth >= 200 || distancenorth <= 0){
    Serial.println("North is out of range");
    //Serial.println("Out of range");
  }
  else {
    Serial.println("North is " + String(distancenorth));
   // Serial.print(distancenorth);
   // Serial.println(" cm");
  }
  delay(1000); */
  Serial.println("East is "+String(distanceeast)+", West is "+String(distancewest)+", South is "+String(distancesouth)+", North is "+String(distancenorth));
  delay(1000);
}
